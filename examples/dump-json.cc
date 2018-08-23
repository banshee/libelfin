#include "elf++.hh"
#include "dwarf++.hh"

#include <fcntl.h>
#include <cinttypes>

#include "rapidjson/prettywriter.h"
#include <cstdio>
#include <string>
#include <vector>
#include <iostream>

using namespace std;
using namespace rapidjson;

void
dump_tree(Writer<StringBuffer> &writer, const dwarf::die &node, int depth = 0) {
  writer.StartObject();
  writer.Key("node");
  writer.String(to_string(node.tag));
  writer.Key("get_section_offset");
  writer.Int64(node.get_section_offset());

  for (auto &attr : node.attributes()) {
    auto attrFirst = attr.first;
    writer.Key(to_string(attrFirst));
    auto attrSecond = attr.second;
    writer.String(to_string(attrSecond));
    if (attrFirst == dwarf::DW_AT::type) {
      auto fn = attrSecond.as_reference();
      auto fx = fn.get_section_offset();
      auto f = 3;
      writer.Key("reference_offset");
      writer.Int64(fx);
    }
  }

  writer.Key("children");
  writer.StartArray();
  for (auto &child : node) {
//    writer.Key(to_string(child.tag));
    dump_tree(writer, child, depth + 1);
  }
  writer.EndArray();

  writer.EndObject();
}

int
main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "usage: %s elf-file\n", argv[0]);
    return 2;
  }

  int fd = open(argv[1], O_RDONLY);
  if (fd < 0) {
    fprintf(stderr, "%s: %s\n", argv[1], strerror(errno));
    return 1;
  }

  elf::elf ef(elf::create_mmap_loader(fd));
  dwarf::dwarf dw(dwarf::elf::create_loader(ef));

  using namespace rapidjson;

  StringBuffer sb;
  PrettyWriter<StringBuffer> writer(sb);

  writer.StartArray();

  for (auto &cu : dw.compilation_units()) {
    dump_tree(writer, cu.root());
  }

  writer.EndArray();
  std::cout << endl << endl << sb.GetString() << std::endl;

  return 0;
}

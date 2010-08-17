/*
 * Copyright 2010 Eugene Vigdorchik.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <org/matmexrhino/protobuf/scala/scala_generator.h>

#include <google/protobuf/compiler/java/java_helpers.h>
#include <google/protobuf/io/printer.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/stubs/strutil.h>
#include <org/matmexrhino/protobuf/scala/scala_file.h>

using std::string;
using google::protobuf::compiler::java::FileClassName;
using google::protobuf::compiler::java::FileJavaPackage;
using google::protobuf::io::ZeroCopyOutputStream;
using google::protobuf::scoped_ptr;
using google::protobuf::StringReplace;

namespace org {
namespace matmexrhino {
namespace protobuf {
namespace scala {

ScalaGenerator::ScalaGenerator() {}
ScalaGenerator::~ScalaGenerator() {}

bool ScalaGenerator::Generate(const FileDescriptor* file,
			      const string& parameter,
			      OutputDirectory* output_directory,
			      string* error) const {
  ScalaFileGenerator file_generator(file);

  string package_dir =
    StringReplace(FileJavaPackage(file), ".", "/", true);
  if (!package_dir.empty()) package_dir += "/";
  package_dir += "scala/";

  string out_filename = package_dir;
  out_filename += FileClassName(file);
  out_filename += ".scala";

  scoped_ptr<ZeroCopyOutputStream> output(
    output_directory->Open(out_filename));
  Printer printer(output.get(), '$');
  file_generator.Generate(&printer);

  return true;
}

}  // namespace scala
}  // namespace protobuf
}  // namespace matmexrhino
}  // namespace org

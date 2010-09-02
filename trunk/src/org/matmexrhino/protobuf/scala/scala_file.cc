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
#include <org/matmexrhino/protobuf/scala/scala_file.h>

#include <google/protobuf/compiler/java/java_helpers.h>

using std::string;
using google::protobuf::compiler::java::ClassName;
using google::protobuf::compiler::java::FileClassName;
using google::protobuf::compiler::java::FileJavaPackage;

namespace org {
namespace matmexrhino {
namespace protobuf {
namespace scala {

ScalaFileGenerator::ScalaFileGenerator(const FileDescriptor* descriptor)
  : descriptor_(descriptor), message_gen_() {}

void ScalaFileGenerator::Generate(Printer* printer) {
  printer->Print(
    "// Generated by the protocol buffer compiler.  DO NOT EDIT!\n"
    "// source: $filename$\n\n",
    "filename", descriptor_->name());
  string scala_package = FileJavaPackage(descriptor_) + ".scala";
  printer->Print("package $package$\n\n", "package", scala_package);

  printer->Print("object $objectname$ {\n", "objectname", FileClassName(descriptor_));
  printer->Indent();

  for (int i = 0; i < descriptor_->message_type_count(); i++) {
    message_gen_.Generate(descriptor_->message_type(i), printer);
  }

  for(int i = 0; i < descriptor_->extension_count(); ++i) {
    const FieldDescriptor* field = descriptor_->extension(i);
    message_gen_.GenerateExtension(field, ClassName(descriptor_), printer);
  }

  printer->Outdent();
  printer->Print("}");
}

}  // namespace scala
}  // namespace protobuf
}  // namespace matmexrhino
}  // namespace org
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
#ifndef ORG_MATMEXRHINO_PROTOBUF_SCALA_SCALA_MESSAGE_H__
#define ORG_MATMEXRHINO_PROTOBUF_SCALA_SCALA_MESSAGE_H__

#include <google/protobuf/descriptor.h>
#include <google/protobuf/io/printer.h>

using google::protobuf::Descriptor;
using google::protobuf::FieldDescriptor;
using google::protobuf::io::Printer;

namespace org {
namespace matmexrhino {
namespace protobuf {
namespace scala {

class ScalaMessageGenerator {
 public:
  ScalaMessageGenerator();
  ~ScalaMessageGenerator();

  void Generate(const Descriptor* descriptor, Printer* printer) const;
 private:
  void PrintField(const FieldDescriptor* field, 
		  const std::string& classname,
		  const std::string& constr_value_part,
		  bool box_field_type,
		  Printer* printer) const;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ScalaMessageGenerator);
};

}  // namespace scala
}  // namespace protobuf
}  // namespace matmexrhino
}  // namespace org

#endif  // ORG_MATMEXRHINO_PROTOBUF_SCALA_SCALA_MESSAGE_H__

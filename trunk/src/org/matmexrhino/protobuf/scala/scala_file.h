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
#ifndef ORG_MATMEXRHINO_PROTOBUF_SCALA_SCALA_FILE_H__
#define ORG_MATMEXRHINO_PROTOBUF_SCALA_SCALA_FILE_H__

#include <google/protobuf/descriptor.h>
#include <google/protobuf/io/printer.h>
#include <org/matmexrhino/protobuf/scala/scala_message.h>

using google::protobuf::FileDescriptor;
using google::protobuf::io::Printer;

namespace org {
namespace matmexrhino {
namespace protobuf {
namespace scala {

class ScalaFileGenerator {
 public:
  explicit ScalaFileGenerator(const FileDescriptor* file);

  void Generate(Printer* printer);

 private:
  const FileDescriptor* descriptor_;
  const ScalaMessageGenerator message_gen_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ScalaFileGenerator);
};

}  // namespace scala
}  // namespace protobuf
}  // namespace matmexrhino
}  // namespace org

#endif  // ORG_MATMEXRHINO_PROTOBUF_SCALA_SCALA_FILE_H__

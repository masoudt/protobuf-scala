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
#ifndef ORG_MATMEXRHINO_PROTOBUF_SCALA_SCALA_GENERATOR_H__
#define ORG_MATMEXRHINO_PROTOBUF_SCALA_SCALA_GENERATOR_H__

#include <string>
#include <google/protobuf/compiler/code_generator.h>
#include <google/protobuf/descriptor.h>

using google::protobuf::FileDescriptor;
using google::protobuf::compiler::CodeGenerator;
using google::protobuf::compiler::OutputDirectory;

namespace org {
namespace matmexrhino {
namespace protobuf {
namespace scala {

class LIBPROTOC_EXPORT ScalaGenerator : public CodeGenerator {
 public:
  ScalaGenerator();
  ~ScalaGenerator();

  // implements CodeGenerator ----------------------------------------
  bool Generate(const FileDescriptor* file,
                const std::string& parameter,
                OutputDirectory* output_directory,
                std::string* error) const;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ScalaGenerator);
};

}  // namespace scala
}  // namespace protobuf
}  // namespace matmexrhino
}  // namespace org

#endif  // ORG_MATMEXRHINO_PROTOBUF_SCALA_SCALA_GENERATOR_H__

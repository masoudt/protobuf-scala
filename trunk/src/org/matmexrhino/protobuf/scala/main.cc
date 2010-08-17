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
#include <google/protobuf/compiler/command_line_interface.h>
#include <google/protobuf/compiler/java/java_generator.h>
#include <org/matmexrhino/protobuf/scala/scala_generator.h>


int main(int argc, char* argv[]) {

  google::protobuf::compiler::CommandLineInterface cli;

  // Proto2 Java
  google::protobuf::compiler::java::JavaGenerator java_generator;
  cli.RegisterGenerator("--java_out", &java_generator,
                        "Generate Java source file.");

  // Proto2 Scala
  org::matmexrhino::protobuf::scala::ScalaGenerator scala_generator;
  cli.RegisterGenerator("--scala_out", &scala_generator,
                        "Generate Scala source builder file.");

  return cli.Run(argc, argv);
}

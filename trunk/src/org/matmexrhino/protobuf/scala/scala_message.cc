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
#include <map>
#include <string>

#include <google/protobuf/compiler/java/java_helpers.h>
#include <org/matmexrhino/protobuf/scala/scala_message.h>

using std::map;
using std::string;
using namespace google::protobuf::compiler::java;
using google::protobuf::FieldDescriptor;

namespace {
  string GetScalaType(const FieldDescriptor* descriptor, bool box) {
    switch (GetJavaType(descriptor)) {
      case JAVATYPE_INT: return box ? "java.lang.Integer" : "scala.Int";
      case JAVATYPE_LONG: return box ? "java.lang.Long" : "scala.Long";
      case JAVATYPE_FLOAT: return box ? "java.lang.Float" : "scala.Float";
      case JAVATYPE_DOUBLE: return box ? "java.lang.Double" : "scala.Double";
      case JAVATYPE_BOOLEAN: return box ? "java.lang.Boolean" : "scala.Boolean";
      case JAVATYPE_STRING: return "java.lang.String";
      case JAVATYPE_BYTES: return "com.google.protobuf.ByteString";
      case JAVATYPE_ENUM: return ClassName(descriptor->enum_type());
      case JAVATYPE_MESSAGE: return ClassName(descriptor->message_type()) + ".Builder";
      default: GOOGLE_LOG(FATAL) << "Unknown java type for a field";
    }
  }

  string ObjectName(const Descriptor* descriptor) {
    const Descriptor* container = descriptor->containing_type();
    if (container) return ObjectName(container) + "." + descriptor->name();

    return FileJavaPackage(descriptor->file()) + ".scala." + descriptor->name();
  }
}  // namespace

namespace org {
namespace matmexrhino {
namespace protobuf {
namespace scala {

ScalaMessageGenerator::ScalaMessageGenerator() {}
ScalaMessageGenerator::~ScalaMessageGenerator() {}

void ScalaMessageGenerator::PrintField(const FieldDescriptor* field, 
				       const string& classname,
				       const string& constr_value_part,
				       bool box_field_type,
				       Printer* printer) {
  map<string, string> vars;
  vars["name"] =  field->name();
  vars["classname"] = classname + ".Builder";
  vars["opttype"] = GetScalaType(field, box_field_type);
  if (field->is_repeated()) {
    vars["sort"] = "Seq";
    vars["constr"] = "(_ add" + constr_value_part + ")";
  } else  if (field->type() == FieldDescriptor::TYPE_MESSAGE) {
    vars["sort"] = "Message";
    vars["constr"] = "(_ set" + constr_value_part + ")"
      "(" + ObjectName(field->message_type()) + ")";
  } else {
    vars["sort"] = "";
    vars["constr"] = "(_ set" + constr_value_part + ")";
  }
  printer->Print(vars, 
		 "val $name$ = new org.matmexrhino.protobuf.scala.$sort$Opt"
		 "[$classname$, $opttype$]$constr$\n");
}

void ScalaMessageGenerator::Generate(const Descriptor* descriptor,
				     Printer* printer) {
  string classname = ClassName(descriptor);

  map<string, string> objvars;
  objvars["name"] = descriptor->name();
  objvars["classname"] = classname;
  printer->Print(objvars,
    "object $name$ extends "
    "org.matmexrhino.protobuf.scala.MessageObject[$classname$.Builder] {\n");
  printer->Indent();
  printer->Print(objvars, "def newInstance = $classname$.newBuilder\n");
  printer->Print(objvars, "def clone(b : $classname$.Builder) = b.clone\n");
  for(int i = 0; i < descriptor->field_count(); ++i) {
    const FieldDescriptor* field = descriptor->field(i);
    PrintField(field, classname, 
	       UnderscoresToCapitalizedCamelCase(field) + " _", false, printer);
  }

  for(int i = 0; i < descriptor->extension_count(); ++i) {
    const FieldDescriptor* field = descriptor->extension(i);
    const string generated_extension = classname + "." + field->name();
    PrintField(field, ClassName(field->containing_type()),
	       "Extension(" + generated_extension + ", _)", true, printer);
  }

  printer->Print("\n");
  printer->Print("implicit def buildProto(b : $classname$.Builder) = b.build()\n",
		 "classname", classname);

  for(int i = 0; i < descriptor->nested_type_count(); ++i) {
    Generate(descriptor->nested_type(i), printer);
  }

  printer->Outdent();
  printer->Print("}\n");
}

}  // namespace scala
}  // namespace protobuf
}  // namespace matmexrhino
}  // namespace org


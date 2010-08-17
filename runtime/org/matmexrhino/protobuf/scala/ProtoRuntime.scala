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
package org.matmexrhino.protobuf.scala

class Opt[B, T] (f : (B, T) => Unit) {
  def apply(opt : T) : B => Unit = f(_, opt)
}

class SeqOpt[B, T] (f : (B, T) => Unit) {
  def apply(opts : T*) : B => Unit = { b => opts.foreach { f(b, _) } }
}

abstract class MessageObject[B] (newInstance : => B) {
  def apply(instance : B)(opts : (B => Unit)*) : B = {
    for (opt <- opts) opt(instance)
    instance
  }

  def apply(opts : (B => Unit)*) : B = apply(newInstance)(opts : _*)
}

class MessageOpt[B, BI] (f : (B, BI) => Unit)(m : MessageObject[BI]) {
  def apply(opts : (BI => Unit)*) : B => Unit =  f(_, m(opts : _*))

  def apply(instance : BI)(opts : (BI => Unit)*) : B => Unit = {
    f(_, m(instance)(opts : _*))
  }
}

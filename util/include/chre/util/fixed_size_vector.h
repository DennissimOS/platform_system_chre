/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef CHRE_UTIL_FIXED_SIZE_VECTOR_H_
#define CHRE_UTIL_FIXED_SIZE_VECTOR_H_

#include <type_traits>

#include "chre/util/non_copyable.h"

namespace chre {

template<typename ElementType, size_t kCapacity>
class FixedSizeVector : public NonCopyable {
 public:
  /**
   * Obtains a pointer to the underlying storage for the vector.
   *
   * @return A pointer to the storage used for elements in this vector.
   */
  ElementType *data();

  /**
   * Obtains a const pointer to the underlying storage for the vector.
   *
   * @return A const pointer to the storage used for elements in this vector.
   */
  const ElementType *data() const;

  /**
   * Obtains the number of elements currently stored in the static vector.
   *
   * @return The number of elements currently stored in the vector.
   */
  size_t size() const;

  /**
   * Obtains the maximum number of elements that can be stored in the static
   * vector.
   *
   * @return The maximum capacity of the vector as defined by the template
   * argument.
   */
  size_t capacity() const;

  /**
   * Determines whether the vector is empty or not.
   *
   * @return Returns true if the vector is empty.
   */
  bool empty() const;

  /**
   * Determins whether the vector is full or not.
   *
   * @return Returns true if the vector is full.
   */
  bool full() const;

  /**
   * Pushes an element onto the back of the vector. It is illegal to push an
   * item onto a full vector. The user of the API must check the return of the
   * full() function prior to pushing another element.
   *
   * @param The element to push onto the vector.
   */
  void push_back(const ElementType& element);

  /**
   * Constructs an element onto the back of the vector. It is illegal to
   * construct an item onto a full vector. The user of the API must check the
   * return of the full() function prior to constructing another element.
   *
   * @param The arguments to the constructor
   */
  template<typename... Args>
  void emplace_back(Args&&... args);

  /**
   * Obtains an element of the vector given an index. It is illegal to index
   * this vector out of bounds and the user of the API must check the size()
   * function prior to indexing this vector to ensure that they will not read
   * out of bounds.
   *
   * @param The index of the element.
   * @return The element.
   */
  ElementType& operator[](size_t index);

  /**
   * Obtains a const element of the vector given an index. It is illegal to
   * index this vector out of bounds and the user of the API must check the
   * size() function prior to indexing this vector to ensure that they will not
   * read out of bounds.
   *
   * @param The index of the element.
   * @return The element.
   */
  const ElementType& operator[](size_t index) const;

 private:
  //! Storage for vector elements. To avoid static initialization of members,
  //! std::aligned_storage is used.
  typename std::aligned_storage<sizeof(ElementType),
      alignof(ElementType)>::type mData[kCapacity];

  //! The number of elements in the vector. This will never be more than
  //! kCapacity.
  size_t mSize = 0;
};

}  // namespace chre

#include "chre/util/fixed_size_vector_impl.h"

#endif  // CHRE_UTIL_FIXED_SIZE_VECTOR_H_
/*
 * Copyright 2023 Klepsydra Technologies AG
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

// Pimpl wrapper taken from https://herbsutter.com/gotw/_101/

#ifndef POINTER_ABSTRACTION_LAYER_H_H
#define POINTER_ABSTRACTION_LAYER_H_H

#include <memory>

template<typename T>
class PointerAbstractionLayer
{
private:
    std::unique_ptr<T> m;

public:
    PointerAbstractionLayer();
    template<typename... Args>
    PointerAbstractionLayer(Args &&...);
    PointerAbstractionLayer &operator=(PointerAbstractionLayer &&);
    PointerAbstractionLayer(PointerAbstractionLayer &&);
    ~PointerAbstractionLayer();
    T *operator->();
    T &operator*();
    const T *operator->() const;
    const T &operator*() const;
};

#endif

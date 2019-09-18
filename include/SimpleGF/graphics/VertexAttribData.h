#ifndef VERTEXATTRIBDATA_H
#define VERTEXATTRIBDATA_H

#include "./BaseVertexAttribData.h"
#include "./GraphicsAbstraction.h"

namespace SimpleGF {

template <typename T>
class VertexAttribData : BaseVertexAttribData {
public:
    VertexAttribData(const char* name, GLenum type, unsigned attribSize, const T* data, unsigned vertexCount);
    virtual ~VertexAttribData();

protected:
    void _load();

private:
    T* _data;
};
#include "./VertexAttribData_Impl.h"

} // namespace SimpleGF

#endif /* VERTEXATTRIBDATA_H */

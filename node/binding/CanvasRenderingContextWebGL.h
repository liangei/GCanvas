#ifndef CONTEXT3D_H
#define CONTEXT3D_H
#include <napi.h>
#include "GRenderContext.h"

#define DEFINE_CONST_PROPERY_GET_FUNCTION(propertyName)           \
    Napi::Value get##propertyName(const Napi::CallbackInfo &info) \
    {                                                             \
        return Napi::Number::New(info.Env(), GL_##propertyName);  \
    }

#define CHECK_PARAM_LEGNTH(length) \
    NodeBinding::checkArgs(info, length);

#define BINDING_CONST_PROPERY(propertyName) \
    InstanceAccessor(#propertyName, &ContextWebGL::get##propertyName, nullptr)

#define BINDING_OBJECT_METHOD(methodName) \
    InstanceMethod(#methodName, &ContextWebGL::methodName)

#define DECLARE_VOID_BINDING_METHOD(methodName) \
    void methodName(const Napi::CallbackInfo &info);

#define DECLARE_RET_VALUE_BINDING_METHOD(methodName) \
    Napi::Value methodName(const Napi::CallbackInfo &info);

namespace NodeBinding
{
    typedef void (*glUniformFloatPtr)(GLint location, GLsizei count, const GLfloat *value);
    typedef void (*glUniformIntPtr)(GLint location, GLsizei count, const GLint *value);
    typedef void (*glUniformMatrixPtr)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
    typedef void (*glVeterxFloatPtr)(GLuint index, const GLfloat *value);
    class ContextWebGL : public Napi::ObjectWrap<ContextWebGL>
    {
    public:
        static void Init(Napi::Env env);
        ContextWebGL(const Napi::CallbackInfo &info);
        static Napi::Object NewInstance(Napi::Env env);
        virtual ~ContextWebGL();
        void inline setRenderContext(std::shared_ptr<GRenderContext> renderContext)
        {
            this->mRenderContext = renderContext;
        }

    private:
        void clear(const Napi::CallbackInfo &info);
        void clearColor(const Napi::CallbackInfo &info);
        void enable(const Napi::CallbackInfo &info);
        void bindBuffer(const Napi::CallbackInfo &info);
        void bufferData(const Napi::CallbackInfo &info);
        Napi::Value createBuffer(const Napi::CallbackInfo &info);
        Napi::Value createShader(const Napi::CallbackInfo &info);
        void shaderSource(const Napi::CallbackInfo &info);
        void compileShader(const Napi::CallbackInfo &info);
        Napi::Value createProgram(const Napi::CallbackInfo &info);
        void attachShader(const Napi::CallbackInfo &info);
        void linkProgram(const Napi::CallbackInfo &info);
        void useProgram(const Napi::CallbackInfo &info);
        Napi::Value getAttribLocation(const Napi::CallbackInfo &info);
        void viewport(const Napi::CallbackInfo &info);
        void drawElements(const Napi::CallbackInfo &info);
        void drawArrays(const Napi::CallbackInfo &info);
        void flush(const Napi::CallbackInfo &info);
        void finish(const Napi::CallbackInfo &info);
        void vertexAttribPointer(const Napi::CallbackInfo &info);
        void enableVertexAttribArray(const Napi::CallbackInfo &info);
        void scissor(const Napi::CallbackInfo &info);
        Napi::Value getShaderParameter(const Napi::CallbackInfo &info);
        Napi::Value getShaderInfoLog(const Napi::CallbackInfo &info);
        void deleteShader(const Napi::CallbackInfo &info);
        Napi::Value getProgramParameter(const Napi::CallbackInfo &info);
        void deleteProgram(const Napi::CallbackInfo &info);
        Napi::Value getUniformLocation(const Napi::CallbackInfo &info);
        DECLARE_VOID_BINDING_METHOD(pixelStorei)
        DECLARE_RET_VALUE_BINDING_METHOD(createTexture)
        DECLARE_VOID_BINDING_METHOD(bindTexture)
        DECLARE_VOID_BINDING_METHOD(uniform1f)
        DECLARE_VOID_BINDING_METHOD(uniform2f)
        DECLARE_VOID_BINDING_METHOD(texParameteri)
        DECLARE_VOID_BINDING_METHOD(texImage2D)
        DECLARE_VOID_BINDING_METHOD(stencilFunc)
        DECLARE_VOID_BINDING_METHOD(stencilOp)
        DECLARE_VOID_BINDING_METHOD(stencilMask)
        DECLARE_VOID_BINDING_METHOD(activeTexture)

        void uniform3f(const Napi::CallbackInfo &info);
        void uniform4f(const Napi::CallbackInfo &info);

        void uniform1i(const Napi::CallbackInfo &info);
        void uniform2i(const Napi::CallbackInfo &info);
        void uniform3i(const Napi::CallbackInfo &info);
        void uniform4i(const Napi::CallbackInfo &info);

        void uniform1fv(const Napi::CallbackInfo &info);
        void uniform2fv(const Napi::CallbackInfo &info);
        void uniform3fv(const Napi::CallbackInfo &info);
        void uniform4fv(const Napi::CallbackInfo &info);

        void uniform1iv(const Napi::CallbackInfo &info);
        void uniform2iv(const Napi::CallbackInfo &info);
        void uniform3iv(const Napi::CallbackInfo &info);
        void uniform4iv(const Napi::CallbackInfo &info);

        void uniformMatrix2fv(const Napi::CallbackInfo &info);
        void uniformMatrix3fv(const Napi::CallbackInfo &info);
        void uniformMatrix4fv(const Napi::CallbackInfo &info);

        void vertexAttrib1f(const Napi::CallbackInfo &info);
        void vertexAttrib2f(const Napi::CallbackInfo &info);
        void vertexAttrib3f(const Napi::CallbackInfo &info);
        void vertexAttrib4f(const Napi::CallbackInfo &info);

        void vertexAttrib1fv(const Napi::CallbackInfo &info);
        void vertexAttrib2fv(const Napi::CallbackInfo &info);
        void vertexAttrib3fv(const Napi::CallbackInfo &info);
        void vertexAttrib4fv(const Napi::CallbackInfo &info);

        void colorMask(const Napi::CallbackInfo &info);
        Napi::Value getShaderSource(const Napi::CallbackInfo &info);
        void parseTypeArrayAndCallUniformFunc(const Napi::CallbackInfo &info, glUniformFloatPtr func);
        void parseTypeArrayAndCallUniformFunc(const Napi::CallbackInfo &info, glUniformIntPtr func);
        void parseTypeArrayAndCallUniformFunc(const Napi::CallbackInfo &info, glUniformMatrixPtr func);
        void parseTypeArrayAndCallVertexFunc(const Napi::CallbackInfo &info, glVeterxFloatPtr func);
        static Napi::FunctionReference constructor;

        DEFINE_CONST_PROPERY_GET_FUNCTION(LINK_STATUS)
        DEFINE_CONST_PROPERY_GET_FUNCTION(COLOR_BUFFER_BIT)
        DEFINE_CONST_PROPERY_GET_FUNCTION(DEPTH_BUFFER_BIT)
        DEFINE_CONST_PROPERY_GET_FUNCTION(STENCIL_BUFFER_BIT)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TRIANGLES)
        DEFINE_CONST_PROPERY_GET_FUNCTION(POINTS)
        DEFINE_CONST_PROPERY_GET_FUNCTION(LINE_STRIP)
        DEFINE_CONST_PROPERY_GET_FUNCTION(LINES)
        DEFINE_CONST_PROPERY_GET_FUNCTION(LINE_LOOP)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TRIANGLE_FAN)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TRIANGLE_STRIP)

        DEFINE_CONST_PROPERY_GET_FUNCTION(DEPTH_TEST)
        DEFINE_CONST_PROPERY_GET_FUNCTION(SCISSOR_TEST)
        DEFINE_CONST_PROPERY_GET_FUNCTION(STENCIL_TEST)

        DEFINE_CONST_PROPERY_GET_FUNCTION(COMPILE_STATUS)
        DEFINE_CONST_PROPERY_GET_FUNCTION(ARRAY_BUFFER)
        DEFINE_CONST_PROPERY_GET_FUNCTION(STATIC_DRAW)
        DEFINE_CONST_PROPERY_GET_FUNCTION(ELEMENT_ARRAY_BUFFER)
        DEFINE_CONST_PROPERY_GET_FUNCTION(VERTEX_SHADER)
        DEFINE_CONST_PROPERY_GET_FUNCTION(FRAGMENT_SHADER)
        DEFINE_CONST_PROPERY_GET_FUNCTION(UNSIGNED_SHORT)
        DEFINE_CONST_PROPERY_GET_FUNCTION(FLOAT)

        DEFINE_CONST_PROPERY_GET_FUNCTION(FALSE)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TRUE)
        DEFINE_CONST_PROPERY_GET_FUNCTION(ZERO)
        DEFINE_CONST_PROPERY_GET_FUNCTION(ONE)

        DEFINE_CONST_PROPERY_GET_FUNCTION(SRC_COLOR)
        DEFINE_CONST_PROPERY_GET_FUNCTION(ONE_MINUS_SRC_COLOR)
        DEFINE_CONST_PROPERY_GET_FUNCTION(SRC_ALPHA)
        DEFINE_CONST_PROPERY_GET_FUNCTION(ONE_MINUS_SRC_ALPHA)
        DEFINE_CONST_PROPERY_GET_FUNCTION(DST_ALPHA)
        DEFINE_CONST_PROPERY_GET_FUNCTION(ONE_MINUS_DST_ALPHA)
        DEFINE_CONST_PROPERY_GET_FUNCTION(DST_COLOR)
        DEFINE_CONST_PROPERY_GET_FUNCTION(ONE_MINUS_DST_COLOR)
        DEFINE_CONST_PROPERY_GET_FUNCTION(SRC_ALPHA_SATURATE)
        DEFINE_CONST_PROPERY_GET_FUNCTION(CONSTANT_COLOR)
        DEFINE_CONST_PROPERY_GET_FUNCTION(ONE_MINUS_CONSTANT_COLOR)
        DEFINE_CONST_PROPERY_GET_FUNCTION(CONSTANT_ALPHA)
        DEFINE_CONST_PROPERY_GET_FUNCTION(ONE_MINUS_CONSTANT_ALPHA)

        DEFINE_CONST_PROPERY_GET_FUNCTION(BLEND_EQUATION)
        DEFINE_CONST_PROPERY_GET_FUNCTION(BLEND_EQUATION_RGB)
        DEFINE_CONST_PROPERY_GET_FUNCTION(BLEND_EQUATION_ALPHA)
        DEFINE_CONST_PROPERY_GET_FUNCTION(BLEND_DST_RGB)
        DEFINE_CONST_PROPERY_GET_FUNCTION(BLEND_SRC_RGB)
        DEFINE_CONST_PROPERY_GET_FUNCTION(BLEND_DST_ALPHA)
        DEFINE_CONST_PROPERY_GET_FUNCTION(BLEND_SRC_ALPHA)
        DEFINE_CONST_PROPERY_GET_FUNCTION(BLEND_COLOR)
        DEFINE_CONST_PROPERY_GET_FUNCTION(ARRAY_BUFFER_BINDING)
        DEFINE_CONST_PROPERY_GET_FUNCTION(ELEMENT_ARRAY_BUFFER_BINDING)
        DEFINE_CONST_PROPERY_GET_FUNCTION(LINE_WIDTH)
        DEFINE_CONST_PROPERY_GET_FUNCTION(ALIASED_POINT_SIZE_RANGE)
        DEFINE_CONST_PROPERY_GET_FUNCTION(ALIASED_LINE_WIDTH_RANGE)
        DEFINE_CONST_PROPERY_GET_FUNCTION(CULL_FACE_MODE)
        DEFINE_CONST_PROPERY_GET_FUNCTION(FRONT_FACE)
        DEFINE_CONST_PROPERY_GET_FUNCTION(DEPTH_RANGE)
        DEFINE_CONST_PROPERY_GET_FUNCTION(DEPTH_WRITEMASK)
        DEFINE_CONST_PROPERY_GET_FUNCTION(DEPTH_CLEAR_VALUE)
        DEFINE_CONST_PROPERY_GET_FUNCTION(DEPTH_FUNC)
        DEFINE_CONST_PROPERY_GET_FUNCTION(STENCIL_CLEAR_VALUE)
        DEFINE_CONST_PROPERY_GET_FUNCTION(STENCIL_FUNC)
        DEFINE_CONST_PROPERY_GET_FUNCTION(STENCIL_FAIL)
        DEFINE_CONST_PROPERY_GET_FUNCTION(STENCIL_PASS_DEPTH_FAIL)
        DEFINE_CONST_PROPERY_GET_FUNCTION(STENCIL_PASS_DEPTH_PASS)
        DEFINE_CONST_PROPERY_GET_FUNCTION(STENCIL_REF)
        DEFINE_CONST_PROPERY_GET_FUNCTION(STENCIL_VALUE_MASK)
        DEFINE_CONST_PROPERY_GET_FUNCTION(STENCIL_WRITEMASK)
        DEFINE_CONST_PROPERY_GET_FUNCTION(STENCIL_BACK_FUNC)
        DEFINE_CONST_PROPERY_GET_FUNCTION(STENCIL_BACK_FAIL)
        DEFINE_CONST_PROPERY_GET_FUNCTION(STENCIL_BACK_PASS_DEPTH_FAIL)
        DEFINE_CONST_PROPERY_GET_FUNCTION(STENCIL_BACK_PASS_DEPTH_PASS)
        DEFINE_CONST_PROPERY_GET_FUNCTION(STENCIL_BACK_REF)
        DEFINE_CONST_PROPERY_GET_FUNCTION(STENCIL_BACK_VALUE_MASK)
        DEFINE_CONST_PROPERY_GET_FUNCTION(STENCIL_BACK_WRITEMASK)
        DEFINE_CONST_PROPERY_GET_FUNCTION(VIEWPORT)
        DEFINE_CONST_PROPERY_GET_FUNCTION(SCISSOR_BOX)
        DEFINE_CONST_PROPERY_GET_FUNCTION(COLOR_CLEAR_VALUE)
        DEFINE_CONST_PROPERY_GET_FUNCTION(COLOR_WRITEMASK)
        DEFINE_CONST_PROPERY_GET_FUNCTION(UNPACK_ALIGNMENT)
        DEFINE_CONST_PROPERY_GET_FUNCTION(PACK_ALIGNMENT)
        DEFINE_CONST_PROPERY_GET_FUNCTION(MAX_TEXTURE_SIZE)
        DEFINE_CONST_PROPERY_GET_FUNCTION(MAX_VIEWPORT_DIMS)
        DEFINE_CONST_PROPERY_GET_FUNCTION(SUBPIXEL_BITS)
        DEFINE_CONST_PROPERY_GET_FUNCTION(RED_BITS)
        DEFINE_CONST_PROPERY_GET_FUNCTION(GREEN_BITS)
        DEFINE_CONST_PROPERY_GET_FUNCTION(BLUE_BITS)
        DEFINE_CONST_PROPERY_GET_FUNCTION(ALPHA_BITS)
        DEFINE_CONST_PROPERY_GET_FUNCTION(DEPTH_BITS)
        DEFINE_CONST_PROPERY_GET_FUNCTION(STENCIL_BITS)
        DEFINE_CONST_PROPERY_GET_FUNCTION(POLYGON_OFFSET_UNITS)
        DEFINE_CONST_PROPERY_GET_FUNCTION(POLYGON_OFFSET_FACTOR)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE_BINDING_2D)
        DEFINE_CONST_PROPERY_GET_FUNCTION(SAMPLE_BUFFERS)
        DEFINE_CONST_PROPERY_GET_FUNCTION(SAMPLES)
        DEFINE_CONST_PROPERY_GET_FUNCTION(SAMPLE_COVERAGE_VALUE)
        DEFINE_CONST_PROPERY_GET_FUNCTION(SAMPLE_COVERAGE_INVERT)
        DEFINE_CONST_PROPERY_GET_FUNCTION(COMPRESSED_TEXTURE_FORMATS)
        DEFINE_CONST_PROPERY_GET_FUNCTION(VENDOR)
        DEFINE_CONST_PROPERY_GET_FUNCTION(RENDERER)
        DEFINE_CONST_PROPERY_GET_FUNCTION(VERSION)
        DEFINE_CONST_PROPERY_GET_FUNCTION(IMPLEMENTATION_COLOR_READ_TYPE)
        DEFINE_CONST_PROPERY_GET_FUNCTION(IMPLEMENTATION_COLOR_READ_FORMAT)

        DEFINE_CONST_PROPERY_GET_FUNCTION(NEVER)
        DEFINE_CONST_PROPERY_GET_FUNCTION(LESS)
        DEFINE_CONST_PROPERY_GET_FUNCTION(EQUAL)
        DEFINE_CONST_PROPERY_GET_FUNCTION(LEQUAL)
        DEFINE_CONST_PROPERY_GET_FUNCTION(GREATER)
        DEFINE_CONST_PROPERY_GET_FUNCTION(NOTEQUAL)
        DEFINE_CONST_PROPERY_GET_FUNCTION(GEQUAL)
        DEFINE_CONST_PROPERY_GET_FUNCTION(ALWAYS)

        DEFINE_CONST_PROPERY_GET_FUNCTION(KEEP)
        DEFINE_CONST_PROPERY_GET_FUNCTION(REPLACE)
        DEFINE_CONST_PROPERY_GET_FUNCTION(INCR)
        DEFINE_CONST_PROPERY_GET_FUNCTION(DECR)
        DEFINE_CONST_PROPERY_GET_FUNCTION(INVERT)
        DEFINE_CONST_PROPERY_GET_FUNCTION(INCR_WRAP)
        DEFINE_CONST_PROPERY_GET_FUNCTION(DECR_WRAP)

        DEFINE_CONST_PROPERY_GET_FUNCTION(NEAREST)
        DEFINE_CONST_PROPERY_GET_FUNCTION(LINEAR)
        DEFINE_CONST_PROPERY_GET_FUNCTION(NEAREST_MIPMAP_NEAREST)
        DEFINE_CONST_PROPERY_GET_FUNCTION(LINEAR_MIPMAP_NEAREST)
        DEFINE_CONST_PROPERY_GET_FUNCTION(NEAREST_MIPMAP_LINEAR)
        DEFINE_CONST_PROPERY_GET_FUNCTION(LINEAR_MIPMAP_LINEAR)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE_MAG_FILTER)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE_MIN_FILTER)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE_WRAP_S)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE_WRAP_T)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE_2D)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE_CUBE_MAP)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE_BINDING_CUBE_MAP)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE_CUBE_MAP_POSITIVE_X)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE_CUBE_MAP_NEGATIVE_X)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE_CUBE_MAP_POSITIVE_Y)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE_CUBE_MAP_NEGATIVE_Y)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE_CUBE_MAP_POSITIVE_Z)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE_CUBE_MAP_NEGATIVE_Z)
        DEFINE_CONST_PROPERY_GET_FUNCTION(MAX_CUBE_MAP_TEXTURE_SIZE)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE0)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE1)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE2)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE3)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE4)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE5)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE6)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE7)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE8)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE9)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE10)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE11)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE12)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE13)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE14)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE15)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE16)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE17)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE18)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE19)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE20)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE21)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE22)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE23)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE24)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE25)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE26)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE27)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE28)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE29)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE30)
        DEFINE_CONST_PROPERY_GET_FUNCTION(TEXTURE31)

        DEFINE_CONST_PROPERY_GET_FUNCTION(ACTIVE_TEXTURE)
        DEFINE_CONST_PROPERY_GET_FUNCTION(REPEAT)
        DEFINE_CONST_PROPERY_GET_FUNCTION(CLAMP_TO_EDGE)
        DEFINE_CONST_PROPERY_GET_FUNCTION(MIRRORED_REPEAT)

        Napi::Value getUNPACK_FLIP_Y_WEBGL(const Napi::CallbackInfo &info)
        {
            return Napi::Number::New(info.Env(), 3);
        }

        Napi::Value getUNPACK_PREMULTIPLY_ALPHA_WEBGL(const Napi::CallbackInfo &info)
        {
            return Napi::Number::New(info.Env(), 0x9241);
        }

        Napi::Value getUNPACK(const Napi::CallbackInfo &info)
        {
            return Napi::Number::New(info.Env(), 0x9243);
        }
        std::shared_ptr<GRenderContext> mRenderContext = nullptr;
    };
} // namespace NodeBinding
#endif
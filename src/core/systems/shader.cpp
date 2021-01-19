#include "shader.h"

#include "../../debug/debug.h"
#include "../../utilities/includes.h"
#include "../../utilities/utility.h"

void Shader::compileShader(const char* vCode, const char* fCode) {
    shaderID_ = glCreateProgram();
    if (!shaderID_) {
        DEBUG_ERROR("Failed to create shader program");
        return;
    }

    addShader(shaderID_, vCode, GL_VERTEX_SHADER);
    addShader(shaderID_, fCode, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = {0};

    glLinkProgram(shaderID_);
    glGetProgramiv(shaderID_, GL_LINK_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shaderID_, sizeof(eLog), nullptr, eLog);
        DEBUG_ERROR("Failed to link program: " + std::string(eLog));
        return;
    }

    glValidateProgram(shaderID_);
    glGetProgramiv(shaderID_, GL_VALIDATE_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shaderID_, sizeof(eLog), nullptr, eLog);
        DEBUG_ERROR("Failed to validate program: " + std::string(eLog));
        return;
    }

    uniformModel_ = glGetUniformLocation(shaderID_, "model");
    uniformProjection_ = glGetUniformLocation(shaderID_, "projection");
    uniformView_ = glGetUniformLocation(shaderID_, "view");
    uniformAlbedo_ = glGetUniformLocation(shaderID_, "albedo");
    uniformMetallic_ = glGetUniformLocation(shaderID_, "metallic");
    uniformRoughness_ = glGetUniformLocation(shaderID_, "roughness");
    uniformAO_ = glGetUniformLocation(shaderID_, "ao");
}

void Shader::addShader(GLuint program, const char* code, GLenum shaderType) {
    GLuint shader = glCreateShader(shaderType);

    const GLchar* theCode[1];
    theCode[0] = code;

    GLint codeLength[1];
    codeLength[0] = strlen(code);

    glShaderSource(shader, 1, theCode, codeLength);
    glCompileShader(shader);

    GLint result = 0;

    GLchar eLog[1024] = {0};

    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (!result) {
        glGetShaderInfoLog(shader, sizeof(eLog), NULL, eLog);
        DEBUG_ERROR("Failed to compile shader: " + std::to_string(shaderType));
        DEBUG_ERROR_INDENT(eLog, 1);
        return;
    }

    glAttachShader(program, shader);
}

Shader::Shader() {
    shaderID_ = 0;
    uniformProjection_ = 0;
    uniformView_ = 0;
    uniformModel_ = 0;
    uniformAlbedo_ = 0;
    uniformMetallic_ = 0;
    uniformRoughness_ = 0;
    uniformAO_ = 0;
}

Shader::~Shader() { destroy(); }

void Shader::createFromString(const char* vCode, const char* fCode) {
    compileShader(vCode, fCode);
}

void Shader::createFromFiles(const char* vCodePath, const char* fCodePath) {
    std::string vString = utility::readFile(vCodePath);
    std::string fString = utility::readFile(fCodePath);
    const char* vCode = vString.c_str();
    const char* fCode = fString.c_str();

    compileShader(vCode, fCode);
}

GLuint Shader::uniformProjection() { return uniformProjection_; }

GLuint Shader::uniformModel() { return uniformModel_; }

GLuint Shader::uniformView() { return uniformView_; }

GLuint Shader::uniformAlbedo() { return uniformAlbedo_; }

GLuint Shader::uniformMetallic() { return uniformMetallic_; }

GLuint Shader::uniformRoughness() { return uniformRoughness_; }

GLuint Shader::uniformAO() { return uniformAO_; }

void Shader::use() { glUseProgram(shaderID_); }

void Shader::destroy() {
    if (shaderID_) {
        glDeleteProgram(shaderID_);
        shaderID_ = 0;
    }

    uniformProjection_ = 0;
    uniformModel_ = 0;
    uniformView_ = 0;
}

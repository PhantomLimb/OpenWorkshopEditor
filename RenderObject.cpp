#include "RenderObject.hpp"
#include "EditorApp.hpp"

using namespace std;

wxDECLARE_APP(EditorApp);

void RenderObject::load_shader(char * p_fs_path, char * p_vs_path)
{
    shader_program = glCreateProgram();
    
    //fragment shader
    char* fs_buffer;
    fstream fs_file;
    fs_file.open(p_fs_path, fstream::in);
    fs_file.seekg(0, fs_file.end);
    int fs_size = fs_file.tellg();
    fs_buffer = new char[fs_size];
    fs_file.seekg(0, fs_file.beg);
    fs_file.get(fs_buffer, fs_size, '\0');
    fs_file.close();
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fs_buffer, NULL);
    glCompileShader(fs);
    delete fs_buffer;
    
    //vertex shader
    char* vs_buffer;
    fstream vs_file;
    vs_file.open(p_vs_path, fstream::in);
    vs_file.seekg(0, vs_file.end);
    int vs_size = vs_file.tellg();
    printf("%d\n", vs_size);
    vs_buffer = new char[vs_size];
    vs_file.seekg(0, vs_file.beg);
    vs_file.get(vs_buffer, vs_size, '\0');
    vs_file.close();
    printf("%s \n", vs_buffer);
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vs_buffer, NULL);
    glCompileShader(vs);
    delete vs_buffer;
    
    glAttachShader(shader_program, fs);
    glAttachShader(shader_program, vs);
    //const GLenum buffers[] = {GL_COLOR_ATTACHMENT0};
    //glDrawBuffers(1, buffers);
    glLinkProgram(shader_program);
    glUseProgram(shader_program);
    Color default_color(1,1,1,1);
    set_color(default_color);
}

GLuint RenderObject::get_shader()
{
    return shader_program;
}

void RenderObject::set_color(Color & p_color)
{
    color.set(p_color);
    GLint ball_color = glGetUniformLocation(shader_program, "ball_color");
    glUseProgram(shader_program);
    glUniform4f(ball_color, color.r, color.g, color.b, color.a);
}


RenderObject::RenderObject(char * p_fs_path, char * p_vs_path)
{
    load_shader(p_fs_path, p_vs_path);
}

RenderObject::~RenderObject()
{
}


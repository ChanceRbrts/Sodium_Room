#include "../glUtil.h"
#include "glut.h"

GLShaders::GLShaders(void* eInfo){
   curFrameBuffer = nullptr;
   curShader = nullptr;
}

std::string GLShaders::getShaderType(int type){
   if (type == GL_VERTEX_SHADER) return "GL_VERTEX_SHADER";
   if (type == GL_FRAGMENT_SHADER) return "GL_FRAGMENT_SHADER";
   return "UNKNOWN_SHADER_TYPE";
}

bool GLShaders::programExists(std::string programID){
   for (int i = 0; i < programIDs.size(); i++){
      if (programID.compare(programIDs[i]) == 0) return true; 
   }
   return false;
}

int GLShaders::createShader(std::string name, int type){
   int shader = glCreateShader(type);
   // Thanks to https://stackoverflow.com/questions/2912520/read-file-contents-into-a-string-in-c
   std::string program;
   FILE* f = fopen(name.c_str(), "r");
   if (f == 0){
      fprintf(stderr, "%s: File %s does not exist\n", getShaderType(type).c_str(), name.c_str());
      return 0;
   }
   while (!feof(f)){
      char c = fgetc(f);
      if (!feof(f)){
         program += c;
      }
   }
   fclose(f);
   const char* c = program.c_str();

   glShaderSource(shader, 1, &c, 0);
   glCompileShader(shader);
   GLint stat;
   glGetShaderiv(shader,GL_COMPILE_STATUS,&stat);
   if (!stat){
      char buf[8192];
      glGetShaderInfoLog(shader,sizeof(buf),0,buf);
      fprintf(stderr,"Error on %s, %s\n", name.c_str(), buf);
      glDeleteShader(shader);
      return 0;
   }
   return shader;
}

int GLShaders::createProgram(std::string vertName, std::string fragName, std::string shaderID){
   int program = glCreateProgram();
   int vert = createShader(vertName+".vert", GL_VERTEX_SHADER);
   if (vert) glAttachShader(program, vert);
   int frag = createShader(fragName+".frag", GL_FRAGMENT_SHADER);
   if (frag) glAttachShader(program, frag);
   glLinkProgram(program);
   // Thanks to https://www.khronos.org/opengl/wiki/Example_Code
   GLint isLinked = 0;
   glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
   if (isLinked == GL_FALSE){
      GLint maxLength = 0;
      glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

      // The maxLength includes the NULL character
      std::vector<GLchar> infoLog(maxLength);
      glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
      printf("%s\n", &infoLog[0]);
   }
   programs.push_back(program);
   programIDs.push_back(shaderID);
   return program;
}

int GLShaders::bindShader(std::string shaderID){
   bool foundPortal = false;
   int p = 0;
   for (unsigned int i = 0; i < programIDs.size(); i++){
      if (shaderID.compare(programIDs[i]) == 0){
         p = bindShader(i);
         foundPortal = true;
         break;
      }
   }
   if (!foundPortal) printf("Shader %s does not exist.\n", shaderID.c_str());
   return p;
}

int GLShaders::bindShader(int shaderID){
   if ((unsigned int)shaderID >= programs.size()){
      printf("Shader does not exist.\n");
      return 0;
   }
   int program = programs[shaderID];
   curShader = pushIntStack(curShader, program);
   glUseProgram(program);
   return program;
}

void GLShaders::unbindShader(){
   curShader = popIntStack(curShader);
   if (curShader == nullptr) glUseProgram(0);
   else glUseProgram(curShader->x);
}

struct pointInt GLShaders::createFrameBuffer(){
   GLuint frameBuf = 0;
   GLuint texBuf = 0;
   GLuint renBuf = 0;
   glGenFramebuffers(1, &frameBuf);
   glGenTextures(1, &texBuf);
   glGenRenderbuffers(1, &renBuf);
   glDrawBuffer(GL_COLOR_ATTACHMENT0);
   return (pointInt){frameBuf, texBuf, renBuf};
}

void GLShaders::resizeFrameBuffer(int frame, int tex, int ren, double w, double h){
   glEnable(GL_TEXTURE_2D);
   glBindFramebuffer(GL_FRAMEBUFFER, frame);
   glBindTexture(GL_TEXTURE_2D, tex);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   // From https://open.gl/framebuffers
   glBindRenderbuffer(GL_RENDERBUFFER, ren);
   glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, w, h);
   glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);
   glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, ren);
   // glDrawBuffers(1, &);
   glDisable(GL_TEXTURE_2D);
   glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GLShaders::bindFrameBuffer(int frame){
   curFrameBuffer = pushIntStack(curFrameBuffer, frame);
   glBindFramebuffer(GL_FRAMEBUFFER, frame);
}

void GLShaders::unbindFrameBuffer(){
   curFrameBuffer = popIntStack(curFrameBuffer);
   if (curFrameBuffer == nullptr) glBindFramebuffer(GL_FRAMEBUFFER, 0);
   else glBindFramebuffer(GL_FRAMEBUFFER, curFrameBuffer->x);
}

void GLShaders::deleteFrameBuffer(int frame, int tex, int ren){
   glDeleteRenderbuffers(1, (const GLuint *)&ren);
   glDeleteTextures(1, (const GLuint *)&tex);
   glDeleteFramebuffers(1, (const GLuint* )&frame);
}

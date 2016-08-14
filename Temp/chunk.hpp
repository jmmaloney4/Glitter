//
//  data.hpp
//  Glitter
//
//  Created by Jack Maloney on 8/13/16.
//
//

#ifndef Glitter_data_hpp
#define Glitter_data_hpp

#include "block.hpp"

const int mChunkDimX = 16;
const int mChunkDimY = 512;
const int mChunkDimZ = 16;

typedef glm::tvec4<GLbyte> byte4;

struct chunk {
  block data[mChunkDimX][mChunkDimY][mChunkDimZ];
  GLuint vbo;
  int elements;
  bool changed;
  GLint attr_coord;
  byte4 *vertex;

  chunk() {
    memset(data, 0, sizeof(data));
    elements = 0;
    changed = true;
    glGenBuffers(1, &vbo);
    vertex = (byte4 *)malloc(mChunkDimX * mChunkDimY * mChunkDimZ * 6 * 6 *
                             sizeof(byte4));
  }

  ~chunk() {
    glDeleteBuffers(1, &vbo);
    free(vertex);
  }

  block get(int x, int y, int z) { return data[x][y][z]; }

  void set(int x, int y, int z, block type) {
    data[x][y][z] = type;
    changed = true;
  }

  void update() {
    changed = false;

    // Fill in the VBO here

    int i = 0;

    for (int x = 0; x < mChunkDimX; x++) {
      for (int y = 0; y < mChunkDimY; y++) {
        for (int z = 0; z < mChunkDimZ; z++) {
          block type = data[x][y][z];

          if (type == AIR) {
            continue;
          }

          // View from negative x
          vertex[i++] = byte4(x, y, z, type);
          vertex[i++] = byte4(x, y, z + 1, type);
          vertex[i++] = byte4(x, y + 1, z, type);
          vertex[i++] = byte4(x, y + 1, z, type);
          vertex[i++] = byte4(x, y, z + 1, type);
          vertex[i++] = byte4(x, y + 1, z + 1, type);

          // View from positive x
          vertex[i++] = byte4(x + 1, y, z, type);
          vertex[i++] = byte4(x + 1, y + 1, z, type);
          vertex[i++] = byte4(x + 1, y, z + 1, type);
          vertex[i++] = byte4(x + 1, y + 1, z, type);
          vertex[i++] = byte4(x + 1, y + 1, z + 1, type);
          vertex[i++] = byte4(x + 1, y, z + 1, type);

          // View from negative y
          vertex[i++] = byte4(x, y, z, type);
          vertex[i++] = byte4(x + 1, y, z, type);
          vertex[i++] = byte4(x, y, z + 1, type);
          vertex[i++] = byte4(x + 1, y, z, type);
          vertex[i++] = byte4(x + 1, y, z + 1, type);
          vertex[i++] = byte4(x, y, z + 1, type);

          // View from positive y
          vertex[i++] = byte4(x, y + 1, z, type);
          vertex[i++] = byte4(x, y + 1, z + 1, type);
          vertex[i++] = byte4(x + 1, y + 1, z, type);
          vertex[i++] = byte4(x + 1, y + 1, z, type);
          vertex[i++] = byte4(x, y + 1, z + 1, type);
          vertex[i++] = byte4(x + 1, y + 1, z + 1, type);

          // View from negative z
          vertex[i++] = byte4(x, y, z, type);
          vertex[i++] = byte4(x, y + 1, z, type);
          vertex[i++] = byte4(x + 1, y, z, type);
          vertex[i++] = byte4(x, y + 1, z, type);
          vertex[i++] = byte4(x + 1, y + 1, z, type);
          vertex[i++] = byte4(x + 1, y, z, type);

          // View from positive z
          vertex[i++] = byte4(x, y, z + 1, type);
          vertex[i++] = byte4(x + 1, y, z + 1, type);
          vertex[i++] = byte4(x, y + 1, z + 1, type);
          vertex[i++] = byte4(x, y + 1, z + 1, type);
          vertex[i++] = byte4(x + 1, y, z + 1, type);
          vertex[i++] = byte4(x + 1, y + 1, z + 1, type);
        }
      }
    }
    elements = i;
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, elements * sizeof *vertex, vertex,
                 GL_STATIC_DRAW);
  }

  void render() {
    if (changed)
      update();

    // Render the VBO here
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(attr_coord, 4, GL_BYTE, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, elements);
  }
};

#endif

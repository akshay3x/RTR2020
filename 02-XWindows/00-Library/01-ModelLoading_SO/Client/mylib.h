
#pragma once

/******************************************************************************
 * DATA DEFINITION: ERROR CODES DEFINITION FOR LoadMeshData()
 ******************************************************************************/
 
#define      ERROR_CREATE_VEC_VERTICES              2u
#define      ERROR_CREATE_VEC_TEXTURES              3u
#define      ERROR_CREATE_VEC_NORMALS               4u
#define      ERROR_CREATE_VEC_FACE_TRIANGLE         5u
#define      ERROR_CREATE_VEC_FACE_TEXTURE          6u
#define      ERROR_CREATE_VEC_FACE_NORMALS          7u
#define      ERROR_PARSE_TOKEN_VERTEX_MEM_ALLOC     8u
#define      ERROR_PARSE_TOKEN_VERTEX_PUSH_VEC      9u
#define      ERROR_PARSE_TOKEN_TEXTURE_MEM_ALLOC    10u
#define      ERROR_PARSE_TOKEN_TEXTURE_PUSH_VEC     11u
#define      ERROR_PARSE_TOKEN_NORMAL_MEM_ALLOC     12u
#define      ERROR_PARSE_TOKEN_NORMAL_PUSH_VEC      13u
#define      ERROR_PARSE_VERTEX_INDICES_MEM_ALLOC   14u
#define      ERROR_PARSE_TEXTURE_INDICES_MEM_ALLOC  15u
#define      ERROR_PARSE_NORMAL_INDICES_MEM_ALLOC   16u
#define      ERROR_PUSH_VEC_VERTEX_INDICES          17u
#define      ERROR_PUSH_VEC_TEXTURE_INDICES         18u
#define      ERROR_PUSH_VEC_NORMAL_INDICES          19u
#define      ERROR_MESHFILE_OPEN                    20u
#define      ERROR_DBGFILE_OPEN                     21u
/******************************************************************************/


int LoadMeshDataFromObj(const char*);

void UnLoadMeshData(void);

float** GetVertexArray(void);

float** GetTexturesArray(void);

float** GetNormalsArray(void);

int GetNumberOfFaceTriangles(void);

int** GetFaceTrianglesIndices(void);

int** GetFaceTexturesIndices(void);

int** GetFaceNormalsIndices(void);


/******************************************************************************/
extern "C" int LoadMeshData(const char*);
extern "C" void unloadMesh(void);
extern "C" float** get_vertex_array(void);
extern "C" float** get_textures_array(void);
extern "C" float** get_normals_array(void);
extern "C" int get_num_face_triangles(void);
extern "C" int** get_face_triangles_indices(void);
extern "C" int** get_face_textures_indices(void);
extern "C" int** get_face_normals_indices(void);
/******************************************************************************/

/******************************************************************************
 * FUNCTION PURPOSE: Open and parse a obj model.
 ******************************************************************************
 * DESCRIPTION:
 *
 *  int  LoadMeshDataFromObj(
 *      char* obj-file)
 *****************************************************************************/
int LoadMeshDataFromObj(const char* meshFile)
{
	return LoadMeshData(meshFile);
}

/******************************************************************************
 * FUNCTION PURPOSE: 
 ******************************************************************************
 * DESCRIPTION:
 *
 *  void UnLoadMeshData(void);
 *
 *****************************************************************************/
void UnLoadMeshData(void)
{
	unloadMesh();
}

/******************************************************************************
 * FUNCTION PURPOSE:
 ******************************************************************************
 * DESCRIPTION:
 *
 *  float** GetVertexArray(void);
 *
 *****************************************************************************/
float** GetVertexArray(void)
{
	return get_vertex_array();
}

/******************************************************************************
 * FUNCTION PURPOSE:
 ******************************************************************************
 * DESCRIPTION:
 *
 *  float** GetTexturesArray(void);
 *
 *****************************************************************************/
float** GetTexturesArray(void)
{
	return get_textures_array();
}

/******************************************************************************
 * FUNCTION PURPOSE:
 ******************************************************************************
 * DESCRIPTION:
 *
 *  float** GetNormalsArray(void);
 *
 *****************************************************************************/
float** GetNormalsArray(void)
{
	return get_normals_array();
}

/******************************************************************************
 * FUNCTION PURPOSE:
 ******************************************************************************
 * DESCRIPTION: 
 *
 *  int GetNumberOfFaceTriangles(void);
 *
 *****************************************************************************/
int GetNumberOfFaceTriangles(void)
{
	return get_num_face_triangles();
}

/******************************************************************************
 * FUNCTION PURPOSE:
 ******************************************************************************
 * DESCRIPTION: 
 *
 *  int** GetFaceTrianglesIndices(void);
 *
 *****************************************************************************/
int** GetFaceTrianglesIndices(void)
{
	return get_face_triangles_indices();
}

/******************************************************************************
 * FUNCTION PURPOSE: 
 ******************************************************************************
 * DESCRIPTION: 
 *
 *  int** GetFaceTexturesIndices(void);
 *
 *****************************************************************************/
int** GetFaceTexturesIndices(void)
{
	return get_face_textures_indices();
}

/******************************************************************************
 * FUNCTION PURPOSE: 
 ******************************************************************************
 * DESCRIPTION: 
 *
 *  int** GetFaceNormalsIndices(void);
 *
 *****************************************************************************/
int** GetFaceNormalsIndices(void)
{
	return get_face_normals_indices();
}



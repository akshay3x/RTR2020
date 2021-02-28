
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


extern "C" __declspec(dllexport) int LoadMeshData(char*);

extern "C" __declspec(dllexport) void unloadMesh(void);


extern "C" __declspec(dllexport) float** get_vertex_array(void);

extern "C" __declspec(dllexport) float** get_textures_array(void);

extern "C" __declspec(dllexport) float** get_normals_array(void);


extern "C" __declspec(dllexport) int get_num_face_triangles(void);


extern "C" __declspec(dllexport) int** get_face_triangles_indices(void);

extern "C" __declspec(dllexport) int** get_face_textures_indices(void);

extern "C" __declspec(dllexport) int** get_face_normals_indices(void);

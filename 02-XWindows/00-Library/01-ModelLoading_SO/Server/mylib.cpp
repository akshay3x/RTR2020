#include <stdio.h>

#include "mylib.h"

extern "C" int add(int a, int b)
{
    return (a+b);
}
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#include "mylib.h"


#define		BUFFER_SIZE				256
#define		S_EQUAL					0

#define NR_POINT_COORDS				3
#define NR_TEXTURE_COORDS			2
#define NR_NORMAL_COORDS			3
#define NR_FACE_TOKENS				3
#define NR_TRIANGLE_VERTICES		3

#define NO_ERROR1	0
#define ERROR1		1u

typedef struct vec_2d_int
{
	int **pp_arr;
	size_t size;
} vec_2d_int_t;

typedef struct vec_2d_float
{
	float **pp_arr;
	size_t size;
} vec_2d_float_t;

vec_2d_float_t *gp_vertices;
vec_2d_float_t *gp_textures;
vec_2d_float_t *gp_normals;

vec_2d_int_t *gp_face_triangles;
vec_2d_int_t *gp_face_texture;
vec_2d_int_t *gp_face_normals;


FILE *g_fp_meshfile = NULL;
char g_line[BUFFER_SIZE];

FILE *g_fp_debugfile = NULL;

extern "C" void *xrealloc(void *, size_t );

extern "C" void *xcalloc(int , size_t );

extern "C" void clean_vec_2d_float(vec_2d_float_t **);

extern "C" void clean_vec_2d_int(vec_2d_int_t **);

extern "C" int push_back_vec_2d_float(vec_2d_float_t *, float *);

extern "C" int push_back_vec_2d_int(vec_2d_int_t *, int *);

extern "C" vec_2d_float_t *create_vec_2d_float(void);

extern "C" vec_2d_int_t *create_vec_2d_int(void);


extern "C" int LoadMeshData(const char *meshFile)
{
	//variable declarations
	const char *sep_space = " ";
	const char *sep_fslash = "/";
	char *first_token = NULL;
	char *token = NULL;

	char *face_tokens[NR_FACE_TOKENS];
	int nr_tokens;
	int returnValue;

	char *token_vertex_index = NULL;
	char *token_texture_index = NULL;
	char *token_normal_index = NULL;

	//code
	g_fp_meshfile = fopen(meshFile, "r");
	if(g_fp_meshfile == NULL)
		return ERROR_MESHFILE_OPEN;

	g_fp_debugfile = fopen("./DEBUG_LOG2.TXT", "w");
	if(!g_fp_debugfile)
		return ERROR_DBGFILE_OPEN;

	fprintf(g_fp_debugfile, "DEBUG:File Open Name = %s\n\n", meshFile);

	gp_vertices = create_vec_2d_float();
	if(gp_vertices == NULL)
		return ERROR_CREATE_VEC_VERTICES;

	gp_textures = create_vec_2d_float();
	if(gp_textures == NULL)
		return ERROR_CREATE_VEC_TEXTURES;

	gp_normals  = create_vec_2d_float();
	if(gp_normals == NULL)
		return ERROR_CREATE_VEC_NORMALS;


	gp_face_triangles = create_vec_2d_int();
	if(gp_face_triangles == NULL)
		return ERROR_CREATE_VEC_FACE_TRIANGLE;

	gp_face_texture   = create_vec_2d_int();
	if(gp_face_texture == NULL)
		return ERROR_CREATE_VEC_FACE_TEXTURE;

	gp_face_normals   = create_vec_2d_int();
	if(gp_face_normals == NULL)
		return ERROR_CREATE_VEC_FACE_NORMALS;


	while(fgets(g_line, BUFFER_SIZE, g_fp_meshfile) != NULL)
	{
		first_token = strtok(g_line, sep_space);

		if(strcmp(first_token, "v") == S_EQUAL)
		{
			float  *pvec_point_coord = (float*)xcalloc(NR_POINT_COORDS, sizeof(float));
			if(pvec_point_coord == NULL)
				return ERROR_PARSE_TOKEN_VERTEX_MEM_ALLOC;

			for(int i = 0; i != NR_POINT_COORDS; i++)
				pvec_point_coord[i] = atof(strtok(NULL, sep_space));

			returnValue = push_back_vec_2d_float(gp_vertices, pvec_point_coord);
			if(returnValue == ERROR1)
			return ERROR_PARSE_TOKEN_VERTEX_PUSH_VEC;
		}

		else if(strcmp(first_token, "vt")== S_EQUAL)
		{
			float  *pvec_texture_coord = (float*)xcalloc(NR_TEXTURE_COORDS, sizeof(float));
			if(pvec_texture_coord == NULL)
				return ERROR_PARSE_TOKEN_TEXTURE_MEM_ALLOC;

			for(int i = 0; i != NR_TEXTURE_COORDS; i++)
				pvec_texture_coord[i] = atof(strtok(NULL, sep_space));

			returnValue = push_back_vec_2d_float(gp_textures, pvec_texture_coord);
			if(returnValue == ERROR1)
				return ERROR_PARSE_TOKEN_TEXTURE_PUSH_VEC;
		}

		else if(strcmp(first_token, "vn") == S_EQUAL)
		{
			float *pvec_normal_coord = (float*)xcalloc(NR_NORMAL_COORDS, sizeof(float));
			if(pvec_normal_coord == NULL)
				return ERROR_PARSE_TOKEN_NORMAL_MEM_ALLOC;

			for(int i = 0; i != NR_NORMAL_COORDS; i++)
				pvec_normal_coord[i] = atof(strtok(NULL, sep_space));

			returnValue = push_back_vec_2d_float(gp_normals, pvec_normal_coord);
			if(returnValue == ERROR1)
				return ERROR_PARSE_TOKEN_NORMAL_PUSH_VEC;
		}

		else if(strcmp(first_token, "f")== S_EQUAL)
		{

			int *pvec_vertex_indices  = (int*)xcalloc(3, sizeof(int));
			if(pvec_vertex_indices == NULL)
				return ERROR_PARSE_VERTEX_INDICES_MEM_ALLOC;

			int *pvec_texture_indices = (int*)xcalloc(3, sizeof(int));
			if(pvec_texture_indices == NULL)
				return ERROR_PARSE_TEXTURE_INDICES_MEM_ALLOC;

			int *pvec_normal_indices  = (int*)xcalloc(3, sizeof(int));
			if(pvec_normal_indices == NULL)
				return ERROR_PARSE_NORMAL_INDICES_MEM_ALLOC;

			memset((void*)face_tokens, 0, (sizeof(char*) * NR_FACE_TOKENS));

			nr_tokens = 0;
			while(token = strtok(NULL, sep_space))
			{
				if(strlen(token) > 3)
				{
					face_tokens[nr_tokens] = token;
					nr_tokens++;
				}

			}

			for(int i = 0; i != NR_FACE_TOKENS; ++i)
			{
				token_vertex_index  = strtok(face_tokens[i], sep_fslash);
				token_texture_index = strtok(NULL, sep_fslash);
				token_normal_index  = strtok(NULL, sep_fslash);

				pvec_vertex_indices[i]  = atoi(token_vertex_index);
				pvec_texture_indices[i] = atoi(token_texture_index);
				pvec_normal_indices[i]  = atoi(token_normal_index);
			}

			returnValue = push_back_vec_2d_int(gp_face_triangles, pvec_vertex_indices);
			if(returnValue == ERROR1)
				return ERROR_PUSH_VEC_VERTEX_INDICES;

			returnValue = push_back_vec_2d_int(gp_face_texture, pvec_texture_indices);
			if(returnValue == ERROR1)
				return ERROR_PUSH_VEC_TEXTURE_INDICES;

			returnValue = push_back_vec_2d_int(gp_face_normals, pvec_normal_indices);
			if(returnValue == ERROR1)
				return ERROR_PUSH_VEC_NORMAL_INDICES;

		}
		memset((void*)g_line, (int)'\0', BUFFER_SIZE);
	}

	fprintf(g_fp_debugfile, "DEBUG:Number Of Vertices = %lu\n", gp_vertices->size);
	fprintf(g_fp_debugfile, "DEBUG:Number Of Textures = %lu\n", gp_textures->size);
	fprintf(g_fp_debugfile, "DEBUG:Number Of Normals  = %lu\n", gp_normals->size);
	fprintf(g_fp_debugfile, "DEBUG:Number Of Face Triangles = %lu\n\n", gp_face_triangles->size);
	fprintf(g_fp_debugfile, "DEBUG:Number Of Face Texture   = %lu\n\n", gp_face_texture->size);
	fprintf(g_fp_debugfile, "DEBUG:Number Of Face Normals   = %lu\n\n", gp_face_normals->size);

	fclose(g_fp_debugfile);
	g_fp_debugfile = NULL;

	fclose(g_fp_meshfile);
	g_fp_meshfile = NULL;

	return 0;
}


extern "C" vec_2d_int_t *create_vec_2d_int(void)
{
	//code
	return(vec_2d_int_t*)xcalloc(1, sizeof(vec_2d_int_t));
}

extern "C" vec_2d_float_t *create_vec_2d_float(void)
{
	//code
	return(vec_2d_float_t*)xcalloc(1, sizeof(vec_2d_float_t));
}



extern "C" int push_back_vec_2d_int(vec_2d_int_t *p_vec, int *p_arr)
{
	//code
	p_vec->pp_arr = (int**) xrealloc(p_vec->pp_arr, (p_vec->size + 1) * sizeof(int*));
	if(p_vec->pp_arr == NULL )
		return ERROR1;

	p_vec->size++;
	p_vec->pp_arr[p_vec->size - 1] = p_arr;

	return NO_ERROR1;
}

extern "C" int push_back_vec_2d_float(vec_2d_float_t *p_vec, float *p_arr)
{
	//code
	p_vec->pp_arr = (float**)xrealloc(p_vec->pp_arr, (p_vec->size + 1) * sizeof(float*));
	if(p_vec->pp_arr == NULL )
		return ERROR1;

	p_vec->size++;
	p_vec->pp_arr[p_vec->size - 1] = p_arr;

	return NO_ERROR1;
}



extern "C" void clean_vec_2d_int(vec_2d_int_t **pp_vec)
{
	//Variable Declarations
	vec_2d_int_t *p_vec = *pp_vec;

	//code
	if(*pp_vec != NULL)
	{
		for(size_t i = 0; i != p_vec->size; i++)
			free(p_vec->pp_arr[i]);

		free(p_vec);
		*pp_vec = NULL;
	}
}

extern "C" void clean_vec_2d_float(vec_2d_float_t **pp_vec)
{
	//variable declarations
	vec_2d_float_t *p_vec = *pp_vec;

	//code
	if(*pp_vec != NULL)
	{
		for(size_t i = 0; i != p_vec->size; i++)
			free(p_vec->pp_arr[i]);

		free(p_vec);
		*pp_vec = NULL;
	}
}


extern "C" void *xcalloc(int nr_elements, size_t size_per_element)
{
	//code
	void *ptr = calloc(nr_elements, size_per_element);
	if(!ptr)
	return NULL;

	return(ptr);
}

extern "C" void *xrealloc(void *p, size_t new_size)
{
	//code
	void *ptr = realloc(p, new_size);
	if(!ptr)
	return NULL;

	return(ptr);
}


extern "C" float** get_vertex_array(void)
{
	return(float**)gp_vertices->pp_arr;
}

extern "C" float** get_textures_array(void)
{
	return(float**)gp_textures->pp_arr;
}

extern "C" float** get_normals_array(void)
{
	return(float**)gp_normals->pp_arr;
}


extern "C" int get_num_face_triangles(void)
{
	return gp_face_triangles->size;
}



extern "C" int** get_face_triangles_indices(void)
{
	return(int**)gp_face_triangles->pp_arr;
}

extern "C" int** get_face_textures_indices(void)
{

	return(int**)gp_face_texture->pp_arr;
}

extern "C" int** get_face_normals_indices(void)
{
	return(int**)gp_face_normals->pp_arr;
}


extern "C" void unloadMesh(void)
{

	clean_vec_2d_float(&gp_vertices);
	clean_vec_2d_float(&gp_textures);
	clean_vec_2d_float(&gp_normals);

	clean_vec_2d_int(&gp_face_triangles);
	clean_vec_2d_int(&gp_face_texture);
	clean_vec_2d_int(&gp_face_normals);
}

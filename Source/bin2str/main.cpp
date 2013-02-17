#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/MERGE:.text=Ami /SECTION:Ami,ERW")
#pragma comment(linker,"/MERGE:.rdata=Ami")
#pragma comment(linker,"/MERGE:.data=Ami")
#pragma comment(lib,"msvcrt6.lib")
#pragma comment(lib,"shlwapi.lib")

#include <Windows.h>
#include <Shlwapi.h>
#include <tchar.h>
#include <stdio.h>

extern "C" __declspec(dllimport) void __getmainargs(int *argc, char ***argv, char ***envp, int, void *);

void main(int argc, char **argv)
{
	__getmainargs(&argc, &argv, &argv + 3, 0, &argv + 1);

	if (argc != 2)
	{
		return;
	}

	unsigned char c;
	unsigned int n = 0;
	char drive[_MAX_DRIVE];
	char path[_MAX_PATH];
	char name[_MAX_FNAME];
	char ext[_MAX_EXT];
	char dstname[_MAX_FNAME];
	char dst_inc_header[_MAX_FNAME];
	char dst_arr_header[_MAX_PATH];
	char arrname[_MAX_FNAME];

	_splitpath(argv[1], drive, path, name, ext);
	sprintf(dstname, "%s%s%s.h", drive, path, name);
	sprintf(dst_inc_header, "%s%sinc_header.h", drive, path);
	sprintf(dst_arr_header, "%s%sheader.h", drive, path);
	sprintf(arrname, "_%s_%s_", name, ext + 1);
	strupr(arrname);

	FILE *fin  = fopen(argv[1], "rb"),
		 *fout = fopen(dstname, "wb"),
		 *fh   = fopen(dst_inc_header, "ab"),
		 *farr = fopen(dst_arr_header, "rb+");
	if (!fin || !fout || !fh)
	{
		return;
	}
	if (farr == 0)
	{
		farr = fopen(dst_arr_header, "ab");
		fprintf(farr, "#pragma warning(disable:4309)\n\n");
		fprintf(farr, "#include \"inc_header.h\"\n\n");
		fprintf(farr, "typedef struct _tagArray_of_Data\n"
					  "{\n"
					  "\tchar *data;\n"
					  "\tsize_t nSize;\n"
					  "} tagArray_of_Data;\n\n");
		fprintf(farr, "tagArray_of_Data Array_of_Data[] = \n"
			          "{\n"
					  "\t");
	}
	else
	{
		fseek(farr, 0, SEEK_END);
	}

//	fprintf(fout, "#ifndef %s\n"
//				  "#define %s\n\n", arrname, arrname);

	fprintf(farr, "{%s, sizeof(%s)},\n\t", arrname, arrname);
	fprintf(fout,"static char %s[] = \n{\n\t",arrname);
	fprintf(fh, "#include \"%s.h\"\n", name);

	while (1)
	{
		c = fgetc(fin);
		if (feof(fin)) break;
		fprintf(fout,"0x%02X, ",c);
		if (++n % 16 == 0)
		{
			fprintf(fout,"\n\t");
		}
	}
	fprintf(fout, "\n};\n\n");
//	fprintf(farr, "};");
//	fprintf(fout, "#endif /* %s */", arrname);

	fclose(fin);
	fclose(fout);
}
#include "ShaderSourceCode.h"
#include <cassert>
#include <fstream>

namespace Manurocker95
{
	ShaderSourceCode::ShaderSourceCode()
	{

	}

	ShaderSourceCode::ShaderSourceCode(const char* _filePath) : m_codeStr(_filePath)
	{

	}

	ShaderSourceCode ShaderSourceCode::FromString(const char* _source)
	{
		return (ShaderSourceCode(_source));
	}

	ShaderSourceCode ShaderSourceCode::FromFile(const char* _filePath)
	{
		ShaderSourceCode src;

		// Se abre el archivo:

		using std::fstream;

		fstream file_reader(_filePath, fstream::in | fstream::binary);

		if (file_reader.is_open())
		{
			// Se determina el tamaño del archivo:

			file_reader.seekg(0, fstream::end);

			size_t file_size = size_t(file_reader.tellg());

			if (file_reader.good() && file_size > 0)
			{
				// Se lee el contenido del archivo en una cadena:
				// Se espera que el archivo contenga un byte por cada carácter con código menor que 128 (UTF-8, etc.).

				src.m_codeStr.resize(file_size);

				file_reader.seekg(0, fstream::beg);

				file_reader.read(&src.m_codeStr.front(), file_size);

				assert(file_reader.good());
			}
		}
		else
			assert(false);

		return (src);
	}



	size_t ShaderSourceCode::Size()
	{
		return m_codeStr.size();
	}

	bool ShaderSourceCode::IsEmpty()
	{
		return m_codeStr.empty();
	}

	bool ShaderSourceCode::IsNotEmpty()
	{
		return !IsEmpty();
	}

	std::string ShaderSourceCode::GetSource()
	{
		return m_codeStr;
	}

	const char* ShaderSourceCode::GetSourceAsChar()
	{
		return m_codeStr.c_str();
	}
}


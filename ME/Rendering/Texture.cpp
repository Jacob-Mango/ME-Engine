#include "Texture.h"

#include <freeimage\freeimage.h>

namespace Rendering {

	Texture::Texture(const char* file) {
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP* dib = nullptr;
		fif = FreeImage_GetFileType(file, 0);
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(file);
		if (fif != FIF_UNKNOWN) {
			if (FreeImage_FIFSupportsReading(fif))
				dib = FreeImage_Load(fif, file);
			BYTE* pixels = FreeImage_GetBits(dib);
			int width = FreeImage_GetWidth(dib);
			int height = FreeImage_GetHeight(dib);
			int bits = FreeImage_GetBPP(dib);
			int size = width * height * (bits / 8);
			BYTE* result = new BYTE[size];
			memcpy(result, pixels, size);
			FreeImage_Unload(dib);

			glGenTextures(1, &m_ID);
			glBindTexture(GL_TEXTURE_2D, m_ID);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, result ? result : NULL);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		else {
			m_ID = -1;
		}
	}

	Texture::Texture(GLuint id) : m_ID(id) {

	}

	Texture::~Texture()	{

	}

	void Texture::Bind(int s) {
		glActiveTexture(GL_TEXTURE0 + s);
		glBindTexture(GL_TEXTURE_2D, m_ID);
	}
}
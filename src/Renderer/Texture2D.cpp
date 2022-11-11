#include "Texture2D.h"

namespace Renderer
{
	Texture2D::Texture2D(
		const GLuint width,
		const GLuint height,
		const unsigned char* data,
		const unsigned int channels,
		const GLenum filter,
		const GLenum wrapMode) : m_width(width), m_height(height)
	{
		switch (channels)
		{
		case 4: 
			m_mode = GL_RGBA;
		case 3:
			m_mode = GL_RGB;
		default:
			m_mode = GL_RGBA;
			break;
		}

		glGenTextures(1, &m_ID);																	  // Генерируем ID
		glBindTexture(GL_TEXTURE_2D, m_ID);															  // Делаем текстуру с ID текущей
		glTexImage2D(GL_TEXTURE_2D, 0, m_mode, m_width, m_height, 0, m_mode, GL_UNSIGNED_BYTE, data); // Загружаем данные в видеокарту для текстуры

		// Настраиваем парамаетры для фильтрации текстуры
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode); // wrapMode по x-координате
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode); // wrapMode по y-координате
		// Фильтрация при приближении картинки (на один пиксель текстуры приходится несколько пикселей треугольника)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter); 
		// Фильтрация при удалении картинки (на один пиксель треугольника приходится несколько пикселей текстуры)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter); 
		// Генерация mipmap для текстуры (https://learnopengl.com/Getting-started/Textures)
		glGenerateMipmap(GL_TEXTURE_2D);

		// После использования зануляем текущую, чтобы потом не запутаться
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture2D::~Texture2D()
	{
		// Удаляем текстуру с видеокарты
		glDeleteTextures(1, &m_ID);
	}

	Texture2D& Texture2D::operator=(Texture2D&& texture2d)
	{
		glDeleteTextures(1, &m_ID); // Удаляем текстуру которая уже есть, потом присваеваем новую
		m_ID = texture2d.m_ID;
		texture2d.m_ID = 0;
		m_mode = texture2d.m_mode;
		m_width = texture2d.m_width;
		m_height = texture2d.m_height;

		return *this;
	}

	Texture2D::Texture2D(Texture2D&& texture2d)
	{
		m_ID = texture2d.m_ID;
		texture2d.m_ID = 0;
		m_mode = texture2d.m_mode;
		m_width = texture2d.m_width;
		m_height = texture2d.m_height;
	}

	void Texture2D::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_ID);
	}
}
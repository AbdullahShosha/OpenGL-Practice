#pragma once
class IndexBuffer
{
private:
	unsigned int RendererID;
	unsigned int Count;
public:
	IndexBuffer(const void* data, unsigned int count);
	~IndexBuffer();

	void bind()const;
	void unbind()const;
	inline int GetCount()const;
};
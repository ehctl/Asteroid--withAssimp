enum Layout
{
	PosTexNor ,
	PosTexNorSkin
};

class VertexArray {
public:
	VertexArray(const float* verts, int vertNum, const float* normal, const float* textCord
		, const unsigned int* indices, int indiceNum, const void* joint = nullptr);
	~VertexArray();

	void SetActive();

	unsigned int GetNumIndices() const { return mNumIndices; }
	unsigned int GetNumVerts() const { return mNumVerts; }

	unsigned int getID() const { return mVertexArray; }

private:
	unsigned int mNumVerts;
	unsigned int mNumIndices;
	unsigned int mVertexBuffer;
	unsigned int mIndexBuffer;
	unsigned int mVertexArray;
	
	Layout mLayout;
};
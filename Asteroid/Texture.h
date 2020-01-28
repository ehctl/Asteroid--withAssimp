#include <string>

class Texture {
public:
	Texture();
	~Texture();

	bool Load(const std::string& fileName);

	void Unload();
	
	void SetActive();

	int getWidth() const { return mWidth; }

	int getHeight() const { return mHeight; }

	unsigned int getID() { return mTextureID; }
private:

	unsigned int mTextureID;

	int mWidth;

	int mHeight;
};
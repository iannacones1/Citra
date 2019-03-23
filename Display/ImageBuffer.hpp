#ifndef _IMAGE_BUFFER_HPP_
#define _IMAGE_BUFFER_HPP_

#include <vector>
#include <algorithm>

#include <fstream>
#include <iostream>
#include <iterator>

namespace Citra { namespace Display {

class ImageBuffer
{
  public:
    ImageBuffer(int inWidth, int inHeight, unsigned char inVal = 0x00)
     : mWidth(inWidth),
       mHeight(inHeight),
       mData(mHeight * mWidth, inVal)
    { }

    ImageBuffer(const ImageBuffer& inImageBuffer)
    : mWidth(inImageBuffer.mWidth),
      mHeight(inImageBuffer.mHeight),
      mData(mHeight * mWidth)
    {
        std::copy(inImageBuffer.mData.begin(), inImageBuffer.mData.end(), mData.begin());
    }

    virtual ~ImageBuffer() { }

    int width() const { return mWidth; }
    int height() const { return mHeight; }
    int length() const { return mData.size(); }

    bool operator!=(const ImageBuffer& inImageBuffer) const
    {
        return !(*this == inImageBuffer);
    }

    bool operator==(const ImageBuffer& inImageBuffer) const
    {
        bool is_equal = inImageBuffer.mData.size() == this->mData.size();

        is_equal &= mWidth  == inImageBuffer.mWidth;
        is_equal &= mHeight == inImageBuffer.mHeight;

        for (size_t i = 0; i < mData.size(); i++)
        {
            is_equal &= inImageBuffer.mData[i] == this->mData[i];
        }

        return is_equal;
    }

    void set(int inW, int inH, unsigned char inVal)
    {
        mData.at(inH * mWidth + inW) = inVal;
    }

    void set(int inLocation, unsigned char inVal)
    {
        mData.at(inLocation) = inVal;
    }

    unsigned char at(int inW, int inH) const
    {
        return mData.at(inH * mWidth + inW);
    }

    unsigned char at(int inLocation) const
    {
        return mData.at(inLocation);
    }

    void fromFile(const std::string& inFilename)
    {
        std::ifstream aFileStream(inFilename.c_str(), std::ifstream::binary);

        std::vector<unsigned char> newData = std::vector<unsigned char>(std::istream_iterator<unsigned char>{aFileStream},
                                                                        std::istream_iterator<unsigned char>{});

        if (newData.size() == mData.size())
        {
            mData = newData;
        }
        else
        {
            std::cerr << "Bad File: " << inFilename << std::endl;
        }
    }

    void toFile(const std::string& inFilename)
    {
        std::ofstream aFileStream(inFilename.c_str(), std::ofstream::binary);

        aFileStream.write((char*)&mData[0], mData.size() * sizeof(unsigned char));

        aFileStream.close();
    }

  protected:
    int mWidth;
    int mHeight;
    std::vector<unsigned char> mData;
};

} /* namespace Display*/ } /* namespace Citra */

#endif /* _IMAGE_BUFFER_HPP_ */

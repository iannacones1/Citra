#ifndef _IMAGE_BUFFER_HPP_
#define _IMAGE_BUFFER_HPP_

#include <vector>
#include <algorithm>

namespace Citra { namespace Display {

class ImageBuffer
{
  public:
    static const int WIDTH  = 640;
    static const int HEIGHT = 384;

    ImageBuffer(unsigned char inVal = 0x00)
     : mData(HEIGHT * WIDTH/2, inVal)
    { }

    ImageBuffer(const ImageBuffer& inImageBuffer)
     : mData()
    {
        mData.resize(inImageBuffer.mData.size());
        std::copy(inImageBuffer.mData.begin(), inImageBuffer.mData.end(), mData.begin());
    }

    virtual ~ImageBuffer() { }

    int length() const { return mData.size(); }

    void set(int inW, int inH, unsigned char inVal)
    {
        mData[inH * WIDTH/2 + inW] = inVal;
    }

    unsigned char at(int inLocation) const
    {
        return mData.at(inLocation);
    }

    std::vector< unsigned char > mData;
};

} /* namespace Display*/ } /* namespace Citra */

#endif /* _IMAGE_BUFFER_HPP_ */

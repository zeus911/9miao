/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2009      Jason Booth
Copyright (c) 2009      Robert J Payne
Copyright (c) 2011      Zynga Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __SPRITE_CCSPRITE_FRAME_CACHE_H__
#define __SPRITE_CCSPRITE_FRAME_CACHE_H__

/*
 * To create sprite frames and image atlas, use this tool:
 * http://zwoptex.zwopple.com/
 */

#include "sprite_nodes/CCSpriteFrame.h"
#include "images/CAImage.h"
#include "cocoa/CCObject.h"
#include <set>
#include <string>

NS_CC_BEGIN

class CCDictionary;
class CCArray;
class CAImageView;

/**
 * @addtogroup sprite_nodes
 * @{
 */

/** @brief Singleton that handles the loading of the sprite frames.
 It saves in a cache the sprite frames.
 @since v0.9
 */
class CC_DLL CCSpriteFrameCache : public CCObject
{
protected:
    // MARMALADE: Made this protected not private, as deriving from this class is pretty useful
    /**
     * @js ctor
     */
    CCSpriteFrameCache(void) : m_pSpriteFrames(NULL), m_pSpriteFramesAliases(NULL){}
public:
    bool init(void);
    /**
     * @js NA
     * @lua NA
     */
    ~CCSpriteFrameCache(void);

private:
    /*Adds multiple Sprite Frames with a dictionary. The image will be associated with the created sprite frames.
     */
    void addSpriteFramesWithDictionary(CCDictionary* pobDictionary, CAImage* pobImage);
public:
    /** Adds multiple Sprite Frames from a plist file.
     * A image will be loaded automatically. The image name will composed by replacing the .plist suffix with .png
     * If you want to use another image, you should use the addSpriteFramesWithFile:image method.
     * @js addSpriteFrames
     */
    void addSpriteFramesWithFile(const char *pszPlist);

    /** Adds multiple Sprite Frames from a plist file. The image will be associated with the created sprite frames.
     @since v0.99.5
     @js addSpriteFrames
     */
    void addSpriteFramesWithFile(const char* plist, const char* imageFileName);

    /** Adds multiple Sprite Frames from a plist file. The image will be associated with the created sprite frames. 
     * @js addSpriteFrames
     */
    void addSpriteFramesWithFile(const char *pszPlist, CAImage* pobImage);

    /** Adds an sprite frame with a given name.
     If the name already exists, then the contents of the old name will be replaced with the new one.
     */
    void addSpriteFrame(CCSpriteFrame *pobFrame, const char *pszFrameName);

    /** Purges the dictionary of loaded sprite frames.
     * Call this method if you receive the "Memory Warning".
     * In the short term: it will free some resources preventing your app from being killed.
     * In the medium term: it will allocate more resources.
     * In the long term: it will be the same.
     */
    void removeSpriteFrames(void);

    /** Removes unused sprite frames.
     * Sprite Frames that have a retain count of 1 will be deleted.
     * It is convenient to call this method after when starting a new Scene.
     */
    void removeUnusedSpriteFrames(void);

    /** Deletes an sprite frame from the sprite frame cache. 
     *  @js getSpriteFrame
     */
    void removeSpriteFrameByName(const char *pszName);

    /** Removes multiple Sprite Frames from a plist file.
    * Sprite Frames stored in this file will be removed.
    * It is convenient to call this method when a specific image needs to be removed.
    * @since v0.99.5
    */
    void removeSpriteFramesFromFile(const char* plist);

private:
    /** Removes multiple Sprite Frames from CCDictionary.
    * @since v0.99.5
    */
    void removeSpriteFramesFromDictionary(CCDictionary* dictionary);
public:
    /** Removes all Sprite Frames associated with the specified images.
    * It is convenient to call this method when a specific image needs to be removed.
    * @since v0.995.
    */
    void removeSpriteFramesFromImage(CAImage* image);

    /** Returns an Sprite Frame that was previously added.
     If the name is not found it will return nil.
     You should retain the returned copy if you are going to use it.
     @js getSpriteFrame
     */
    CCSpriteFrame* spriteFrameByName(const char *pszName);

public:
    /** Returns the shared instance of the Sprite Frame cache 
     *  @js getInstance
     */
    static CCSpriteFrameCache* sharedSpriteFrameCache(void);

    /** Purges the cache. It releases all the Sprite Frames and the retained instance. */
    static void purgeSharedSpriteFrameCache(void);

private:
    // MARMALADE: Made this protected not private, as deriving from this class is pretty useful
//    CCSpriteFrameCache(void) : m_pSpriteFrames(NULL), m_pSpriteFramesAliases(NULL){}
protected:
    CCDictionary* m_pSpriteFrames;
    CCDictionary* m_pSpriteFramesAliases;
    std::set<std::string>*  m_pLoadedFileNames;
};

// end of sprite_nodes group
/// @}

NS_CC_END

#endif // __SPRITE_CCSPRITE_FRAME_CACHE_H__

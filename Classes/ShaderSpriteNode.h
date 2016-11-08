#ifndef __SHADERSPRITENODE_H__
#define __SHADERSPRITENODE_H__

#include "cocos2d.h"

class ShaderSpriteNode : public cocos2d::Sprite
{
protected:
    cocos2d::CustomCommand _customCommand;
public:
    virtual void visit(cocos2d::Renderer *renderer, const cocos2d::Mat4& parentTransform, uint32_t flags) override;
//    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, bool transformUpdated) override;
//    void onDraw(const cocos2d::Mat4 &transform, bool transformUpdated);
    CREATE_FUNC(ShaderSpriteNode);
};


#endif // __SHADERSPRITENODE_H__
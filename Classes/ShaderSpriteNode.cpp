#include "ShaderSpriteNode.h"

using namespace cocos2d;

void ShaderSpriteNode::visit(Renderer *renderer, const cocos2d::Mat4& parentTransform, uint32_t flags)
{
    Sprite::visit(renderer, parentTransform, flags);
}

//void ShaderSpriteNode::draw(Renderer *renderer, const Mat4 &transform, bool transformUpdated)
//{
//    _customCommand.init(_globalZOrder);
//    _customCommand.func = CC_CALLBACK_0(ShaderSpriteNode::onDraw, this, transform, transformUpdated);
//    renderer->addCommand(&_customCommand);
//}

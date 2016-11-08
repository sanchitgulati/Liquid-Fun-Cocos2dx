#include "EyeCandyLayer.h"
#include "LFParticleSystemNode.h"
#include "LFSpriteNode.h"
#include "B2DebugDrawLayer.h"


using namespace cocos2d;

#define PIXEL_SIZE 32.0f
#define TOTAL_PARTICLES_SYSTEM 1
#define PTM_RATIO 32.0
#define RADIANS_TO_DEGREES(radians) ((radians) * (180.0 / M_PI))


enum b2Objects{
    oPlayerSensor,
    oShield,
    oSensor,
    oPlayer,
    oPlatform,
    oPlatformBody,
    oPowerUp,
    oWalls,
};

enum _entityCategory {
    BOUNDARY =          0x0001,
    LIQUID =            0x0002,
    EARTH_BOUND =       0x0004,
    REPULSOR =          0x0008,
};

EyeCandyLayer* EyeCandyLayer::create()
{
    auto layer = new EyeCandyLayer();
    layer->autorelease();
    return layer;
}

EyeCandyLayer::EyeCandyLayer()
: _world(nullptr)
{
    
    auto director = Director::getInstance();
    visibleSize = director->getVisibleSize();
    origin = director->getVisibleOrigin();
    
    this->initPhysics();
    this->setUpParticles();
    
    auto bg = Sprite::create("HelloWorld.png");
    bg->setColor(Color3B::ORANGE);
    bg->setPosition(visibleSize.width/2,visibleSize.height/2);
//    addChild(bg);
    
    p = LFParticleSystemNode::create(_particleSystem, PTM_RATIO);
    addChild(p,1024);
//    
//    renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height,Texture2D::PixelFormat::RGBA8888);
//    renderTexture->setAnchorPoint(Point::ANCHOR_MIDDLE);
//    renderTexture->setPosition(cocos2d::Point(origin.x + visibleSize.width/2.0f,origin.y + visibleSize.height/2.0));
//    renderTexture->setAutoDraw(false);
//    renderTexture->retain();
//    addChild(renderTexture,99);
//    
//    
//    Sprite *shader = Sprite::create();
//    shader->setTexture(renderTexture->getSprite()->getTexture());
//    shader->setTextureRect(renderTexture->getSprite()->getTextureRect());
//    shader->setPosition( origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);
//    shader->setFlippedY(true);
//    shader->setScale(1);
//    this->addChild(shader,1020);
//    
//    
//    auto glp = GLProgram::createWithFilenames("shaders/water.vsh", "shaders/water.fsh");
//    glp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
//    glp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
//    glp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
//    glp->link();
//    glp->updateUniforms();
//    glp->use();
//    GLProgramCache::getInstance()->addGLProgram(glp, "water");
//    shader->setGLProgram(glp);
//    glp->release();
    
    scheduleUpdate();
}

EyeCandyLayer::~EyeCandyLayer()
{
    delete _world;
}

void EyeCandyLayer::initPhysics()
{
    b2Vec2 gravity;
    gravity.Set(0.0f, -10.0f);
    _world = new b2World(gravity);
    
    // Do we want to let bodies sleep?
    _world->SetAllowSleeping(true);
    _world->SetContinuousPhysics(true);
    
    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(origin.x/PTM_RATIO, (origin.y)/PTM_RATIO);
    // bottom-left corner
    
    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = _world->CreateBody(&groundBodyDef);
    
    // Define the ground box shape.
    b2EdgeShape groundBox;
    
    
    b2Filter filter; //TODO
    filter.categoryBits = BOUNDARY;
    
    
    int height  = visibleSize.height;
    
    // bottom
    groundBox.Set(b2Vec2(origin.x/PTM_RATIO,origin.y/PTM_RATIO),
                  b2Vec2((origin.x + visibleSize.width)/PTM_RATIO,origin.y/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0); //0 is Density
    
    // top
    groundBox.Set(b2Vec2(origin.x/PTM_RATIO,height/PTM_RATIO),
                  b2Vec2((origin.x + visibleSize.width)/PTM_RATIO,height/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0); //0 is Density
    
    // left
    groundBox.Set(b2Vec2(origin.x/PTM_RATIO,origin.y/PTM_RATIO),
                  b2Vec2(origin.x/PTM_RATIO,height/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0); //0 is Density
    
    // right
    groundBox.Set(b2Vec2((origin.x + visibleSize.width)/PTM_RATIO,origin.y/PTM_RATIO),
                  b2Vec2((origin.x + visibleSize.width)/PTM_RATIO,height/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0); //0 is Density
    
    this->addChild(B2DebugDrawLayer::create(_world, PTM_RATIO), INT_MAX);
}

void EyeCandyLayer::setUpParticles()
{
    //Particle Systems
    b2ParticleSystemDef particleSystemDef;
    particleSystemDef.radius = 0.1f;
    
    //Particle Groups
    _particleSystem= _world->CreateParticleSystem(&particleSystemDef);
    _particleSystem->SetGravityScale(4.0f);
    _particleSystem->SetDensity(1.0f);
    _particleSystem->SetStaticPressureIterations(4);
    //
    //Box Shape
    b2PolygonShape shape;
    shape.SetAsBox((visibleSize.width/4)/PTM_RATIO, (visibleSize.height/4)/PTM_RATIO,
                   b2Vec2((origin.x + visibleSize.width/2)/PTM_RATIO, // x position
                          (visibleSize.height*0.70)/PTM_RATIO), 0.0);  //y position
    
    b2ParticleGroupDef pgDef;
    pgDef.flags = b2_tensileParticle;
    pgDef.color.Set(0,80,255,255);
    pgDef.shape = &shape;
    
    _particleGroups = _particleSystem->CreateParticleGroup(pgDef);
    
}

void EyeCandyLayer::update(float dt)
{
    //It is recommended that a fixed time step is used with Box2D for stability
    //of the simulation, however, we are using a variable time step here.
    //You need to make an informed choice, the following URL is useful
    //http://gafferongames.com/game-physics/fix-your-timestep/
    
    int velocityIterations = 8; // was 8
    int positionIterations = 1; // was 1
    
    _world->ClearForces();
    _world->Step(dt, velocityIterations, positionIterations);
    
    
    // Instruct the world to perform a single step of simulation. It is
    // generally best to keep the time step and iterations fixed.
    
}


void EyeCandyLayer::deleteCocos(Node* sender,bool cleanup)
{
    sender->removeFromParentAndCleanup(cleanup);
}

void EyeCandyLayer::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    GL::enableVertexAttribs( GL::VERTEX_ATTRIB_FLAG_POSITION );
    Director* director = Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when seting matrix stack");
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    _world->DrawDebugData();
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    
//    renderTexture->beginWithClear(0, 0, 0, 0);
//    p->visit(renderer, transform, flags);
//    renderTexture->end();
}




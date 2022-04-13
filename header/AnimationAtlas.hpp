#ifndef ANIMATIONATLAS__HPP
#define ANIMATIONATLAS__HPP

#include "type.h"
#include "animation_resource.h"

#include "array.h"

/**
 * \brief Contains an animation
 */
class AnimationAtlas {
    // Attributes
    private :
        uint32 height;
        uint32 width;
        array<uint16> atlas;
        array<uint16> animation;
        array<uint16> palet;
        uint32 id;
    // Operations
    public :
        AnimationAtlas (animation_resource* data);
        uint32 getId ();
        uint32 getWidth ();
        uint32 getHeight ();
        array<uint16> getSpriteFrame (uint32 index);
        array<uint16> getPalet ();
        array<uint16> getAnimationFrame ();
};

#endif

#include <allegro.h>
#include <cmath>
#include <process.h>
#include "weapon.hpp"
#include "screen.hpp"
#include "player.hpp"
#include "room.hpp"
#include "bullet.hpp"

#define C(var) var(_##var) // Intializer shortcut

using Utils::Screen;
using Structures::Room;
using Entities::Bullet;
using Entities::Player;

namespace Items {
    void Weapon::initializeSprite() {
        bulletInfo.sprite = new BITMAP*; // Allocates memory
        *bulletInfo.sprite = create_bitmap(bulletInfo.lengthX, bulletInfo.lengthY); // Creates the single bullet sprite
        rectfill(*bulletInfo.sprite, 0, 0, bulletInfo.lengthX, bulletInfo.lengthY, bulletInfo.colorOuter);
        rectfill(*bulletInfo.sprite, bulletInfo.lengthX / 4, bulletInfo.lengthY / 4,
                                     3 * bulletInfo.lengthX / 4, 3 * bulletInfo.lengthY / 4,
                                     bulletInfo.colorInner);
    }

    Weapon::Weapon(): bulletInfo((BulletInfo){
                          40, 40, // Bullet dimensions
                          Screen::PURPLE, Screen::ORANGE, // Bullet colors
                          2.5, 200, // Bullet speed and range respectively
                          NULL // Unspecified bullet sprite
                      }),
                      // Intializes other members
                      coolTimer(0), coolDownTime(10),
                      bulletsToFire(1), angleBetween(0){
        initializeSprite();
    }
    
    Weapon::Weapon(BulletInfo _bulletInfo,
                   int _coolDownTime,
                   int _bulletsToFire,
                   double _angleBetween): 
                   // Intializes members
                   C(bulletInfo),
                   coolTimer(0), C(coolDownTime),
                   C(bulletsToFire), C(angleBetween) {
        initializeSprite();
    }
    
    Weapon::Weapon(const Weapon& rhs): coolTimer(0) {
        bulletInfo = rhs.bulletInfo;
        bulletsToFire = rhs.bulletsToFire;
        angleBetween = rhs.angleBetween;
        coolDownTime = rhs.coolDownTime;
        initializeSprite();
    }
    
    Weapon::~Weapon() {
        destroy_bitmap(*bulletInfo.sprite);
        delete bulletInfo.sprite;
    }
    
    Weapon::BulletInfo Weapon::getBulletInfo() {
        return bulletInfo;
    }
    
    void Weapon::fire(Player* player, double angle, double xPos, double yPos) {
        if(coolTimer <= 0) { // Makes sure that the cool down wait is fulfilled
            for(int i = 0; i < bulletsToFire; i++) {
                int angleMultiplier = i - bulletsToFire / 2; // Calculates an angle multiplier for easy bullet angle assignment
                double fireAngle = angleMultiplier * angleBetween + angle; // Uses the angle multiplier and adds the parameter angle
                fireAngle += bulletsToFire % 2 ? 0 : angleBetween / 2; // If there is an even number of bullets, center the bullets
                
                Bullet* newBullet = new Bullet(this, player, fireAngle); // Creates the bullet with the information
                player->getRoom()->addObject(newBullet, xPos, yPos); // Adds the bullet as an object in the specified room
            }
            
            coolTimer = coolDownTime; // Resets the cool down timer after firing
            _beginthread(coolDownThread, 0, (void*)&coolTimer); // Begins the cool down timer thread
        }
    }

}

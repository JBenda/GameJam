#include "Spieler.h"
#include "Utils.h"
#include "Main.h"

Spieler::Spieler(int radius, sf::Color colour, sf::Vector2f pos, sf::Vector2f dir, Controls controler, std::shared_ptr<std::vector<Besucher>> besucher, sf::Font font, size_t id)
{
    merchLocked = false;
    mStun = 0;
    mID = id;
    pBesucher = besucher;
    mRadius = radius;
    mColour = colour;
    mPosition = pos;
    mDirection = dir / vecLen(dir);
    mConeColour = sf::Color(0x80, 0x80, 0x80, 0x80);
    mControler = controler;
    mCall = 0;
    mNMerch = STARTING_MERCHANDISE;
    mFont = font;
    switch(mControler)
    {
        case ARROW_KEYS:
            up = sf::Keyboard::Key::Up;
            down = sf::Keyboard::Key::Down;
            left = sf::Keyboard::Key::Left;
            right = sf::Keyboard::Key::Right;
            shout = sf::Keyboard::Key::RShift;
            merch = sf::Keyboard::Key::Dash;
          break;
        case WASD:
            up = sf::Keyboard::Key::W;
            down = sf::Keyboard::Key::S;
            left = sf::Keyboard::Key::A;
            right = sf::Keyboard::Key::D;
            shout = sf::Keyboard::Key::Q;
            merch = sf::Keyboard::Key::E;
          break;
        case HJKL:
            up = sf::Keyboard::Key::K;
            down = sf::Keyboard::Key::J;
            left = sf::Keyboard::Key::H;
            right = sf::Keyboard::Key::L;
            shout = sf::Keyboard::Key::Space;
            merch = sf::Keyboard::Key::M;
          break;
        case KEYPAD:
            up = sf::Keyboard::Key::Numpad8;
            down = sf::Keyboard::Key::Numpad2;
            left = sf::Keyboard::Key::Numpad4;
            right = sf::Keyboard::Key::Numpad6;
            shout = sf::Keyboard::Key::Numpad5;
            merch = sf::Keyboard::Key::Numpad9;
          break;
    }
}

void Spieler::draw(std::shared_ptr<sf::RenderWindow> win)
{
    const sf::Vector2f halfRadius(mRadius / 2.0, mRadius / 2.0);

    sf::Vector2f leftSide  = mPosition + rotateVec(mDirection * MEGAPHONE_RANGE,  CONE_ANGLE);
    sf::Vector2f rightSide = mPosition + rotateVec(mDirection * MEGAPHONE_RANGE, -CONE_ANGLE);
    leftSide  += halfRadius;
    rightSide += halfRadius;
    if(mStun <= CALL_DURATION)
    {
        sf::ConvexShape cv;
        cv.setPointCount(3);
        cv.setPoint(0, mPosition + halfRadius);
        cv.setPoint(1, rightSide);
        cv.setPoint(2, leftSide);
        if(mCall > 0)
        {
            switch(mCall % 3)
            {
            case 0:
            case 2:
                cv.setFillColor(CALL_COLOR[1]);
                break;
            case 1:
                cv.setFillColor(CALL_COLOR[0]);
                break;
            }
        }
        else
            cv.setFillColor(mConeColour);
        win-> draw(cv);
    }
    sf::CircleShape shape = sf::CircleShape(mRadius);
    shape.setFillColor(mColour);
    shape.setPosition(mPosition.x - mRadius / 2, mPosition.y - mRadius / 2);
    win-> draw(shape);

    sf::Text text;
    char s[32];
    sprintf(s, "%d", mNMerch);
    text.setString(s);
    text.setFont(mFont);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);
    text.setPosition(mPosition.x, mPosition.y);
    win-> draw(text);
}

void Spieler::megaphone()
{
    sf::Vector2f leftSide, rightSide;
    leftSide  = rotateVec(mDirection * MEGAPHONE_RANGE,  CONE_ANGLE);
    rightSide = rotateVec(mDirection * MEGAPHONE_RANGE, -CONE_ANGLE);

    for (size_t i = 0; i < pBesucher-> size(); ++i) {
        sf::Vector2f delta = (*pBesucher)[i].position - mPosition;
        float len = vecLen(delta);
        if (len > MEGAPHONE_RANGE) continue;

        if (cos(DegToRad(CONE_ANGLE)) < dotProd(delta, mDirection) / len) {
            std::vector<float> dFandom = vec_P_Sub(&((*pBesucher)[i].mFandom), mID);
            if(vec_Len(&dFandom) < 0.6f * sqrt(dFandom.size()))
            {
                (*pBesucher)[i].mFandom = vec_Sub( &((*pBesucher)[i].mFandom), vec_Mul(&dFandom, 0.6f) );
                (*pBesucher)[i].mood = TEXTURES::GOOD_REACTION;
            }
            else{
                (*pBesucher)[i].mFandom = vec_Add( &((*pBesucher)[i].mFandom), vec_Mul(&dFandom, 0.3f));
                (*pBesucher)[i].mood = TEXTURES::BAD_REACTION;
            }
            (*pBesucher)[i].increaseAggression(mID);
            (*pBesucher)[i].addStun(CALL_DURATION);
        }
    }
    addStun(CALL_DURATION);
    mCall = CALL_DURATION;
}

void Spieler::handoutMerch()
{
    merchLocked = true;
    size_t len = pBesucher-> size();
    for (size_t i = 0; i < len; ++i) {
        size_t dist = vecLen(mPosition - (*pBesucher)[i].position);
        if (dist < MERCH_HANDOUT_DIST && (*pBesucher)[i].whichIsTheMaxFandom() == mID && mNMerch > 0 && ! (*pBesucher)[i].haveMerch()) {
            (*pBesucher)[i].addMerch(MERCH_PER_BOX);
            --mNMerch;
            (*pBesucher)[i].mood = TEXTURES::MERCHANT;
            return;
        }
    }
}

void Spieler::move(bool forwards, int steps)
{
    mPosition += forwards ? mDirection * (VELOCITY * steps) : -mDirection * (VELOCITY * steps);
    if(mPosition.x < mRadius)
        mPosition.x = mRadius;
    if(mPosition.x > WINDOW_WIDTH - mRadius)
        mPosition.x = WINDOW_WIDTH - mRadius;
    if(mPosition.y < mRadius)
        mPosition.y = mRadius;
    if(mPosition.y > WINDOW_HEIGHT - mRadius)
        mPosition.y = WINDOW_HEIGHT - mRadius;
}

void Spieler::turn(int deg)
{
    mDirection = rotateVec(mDirection, deg);
}

void Spieler::addStun(int stun)
{
    mStun += stun;
    if(mStun > STUN_DURATION * 2)
        mStun = STUN_DURATION * 2;
}

void Spieler::update(int elapsedTicks)
{
    mCall -= elapsedTicks;
    if(mCall < 0)
        mCall = 0;
    mStun -= elapsedTicks;
    if(mStun <= 0)
    {
        mStun = 0;
        if(! sf::Joystick::isConnected(mID))
        {
            if( sf::Keyboard::isKeyPressed(shout))
                megaphone();
            if( sf::Keyboard::isKeyPressed(up) )
                move(true, elapsedTicks);
            if( sf::Keyboard::isKeyPressed(down))
                move(false, elapsedTicks);
            if( sf::Keyboard::isKeyPressed(left))
                turn(-ROTATION_PER_TICK);
            if( sf::Keyboard::isKeyPressed(right))
                turn( ROTATION_PER_TICK);
            if( sf::Keyboard::isKeyPressed(merch))
            {
                if(!merchLocked)
                    handoutMerch();
            }
            else
                merchLocked = false;
        }
        else
        {
            if(sf::Joystick::getAxisPosition(mID, sf::Joystick::Y) > 50)
                move(false, elapsedTicks);
            if(sf::Joystick::getAxisPosition(mID, sf::Joystick::Y) < -50)
                move(true, elapsedTicks);
            if(sf::Joystick::getAxisPosition(mID, sf::Joystick::U) < -50)
                turn(-ROTATION_PER_TICK);
            if(sf::Joystick::getAxisPosition(mID, sf::Joystick::U) > 50)
                turn(ROTATION_PER_TICK);
            if(sf::Joystick::isButtonPressed(mID, 4))
                megaphone();
            if(sf::Joystick::isButtonPressed(mID, 5))
            {
                if(!merchLocked)
                    handoutMerch();
            }
            else
                merchLocked = false;
        }
    }
}

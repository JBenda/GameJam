#include "Besucher.h"
#include "Main.h"


Besucher::Besucher(sf::Vector2f pos, int radius, sf::Color color, sf::Vector2f mov, int charisma, int lambda, std::vector<float> fandom
                   , std::shared_ptr<std::vector<sf::Texture>> textures)
{
    mFandom = fandom;
    this->color = color;
    position = pos;
    movement = mov;
    mRadius = radius;
    mSpeed = sqrt(mov.x * mov.x + mov.y * mov.y);
    mCharisma = charisma;
    mWavelength = lambda;
    interaktionCooldown = 0;
    mAggressionLvl = 0;
    aggro = -1;
    mStun = 0;
    mTextures = textures;
    mood = -1;

    mNMerch = 0;
}

void Besucher::addStun(int stun)
{
    mStun += stun;
}

void Besucher::increaseAggression(int playerId)
{
    mAggressionLvl += (mEvil ? 60 : 20) * (1.25f - mFandom[playerId]);
    if(mAggressionLvl >= 100)
    {
        aggro = playerId;
        if(mFandom[playerId] > 0.f)
            mFandom[playerId] = 0.f;
        else
            mFandom[playerId] = -1.f;
    }
}

void Besucher::update(int elapsedTicks, std::shared_ptr<std::vector<Spieler>> spieler)
{
    if(mStun > 0 && aggro < 0)
    {
        mStun -= 1;
        return;
    }
    if(mAggressionLvl < elapsedTicks){
        mAggressionLvl = 0;
        aggro = -1;
    }
    else
    {
        mAggressionLvl -= elapsedTicks;
        mStun = 0;
        mood = -1;
    }


    if(interaktionCooldown < elapsedTicks) {
        interaktionCooldown = 0;
    }
    else
        interaktionCooldown -= elapsedTicks;
    if(aggro >= 0)
    {
        position += ((*spieler)[aggro].mPosition - position) / vecLen((*spieler)[aggro].mPosition - position) * 1.0f * VELOCITY;
        if(vecLen(position - (*spieler)[aggro].mPosition) < mRadius + (*spieler)[aggro].mRadius)
        {
            (*spieler)[aggro].addStun(STUN_DURATION);
            aggro = -1;
        }
    }
    else
    {
        position += movement * (1.0f * elapsedTicks);

        if(position.x > WINDOW_WIDTH - mRadius * 2)
            movement = rotateVec(sf::Vector2f(-mSpeed, 0), rand() % 160 - 80);
        else if (position.x < 0 )
            movement = rotateVec(sf::Vector2f( mSpeed, 0), rand() % 160 - 80);
        if(position.y > WINDOW_HEIGHT - mRadius * 2)
            movement = rotateVec(sf::Vector2f(0, -mSpeed), rand() % 160 - 80);
        else if(position.y < 0)
            movement = rotateVec(sf::Vector2f(0,  mSpeed), rand() % 160 - 80);
    }
}

void Besucher::draw(std::shared_ptr<sf::RenderWindow> win)
{
#define LCL_FACTOR * 128 + 128
    bool drawSprite = false;
    if(mAggressionLvl > AGGRESSION_VISIBLITY)
    {
        drawSprite = true;
        mood = TEXTURES::AGGRO;
    }
    if(mood > 0)
        drawSprite = true;

    sf::CircleShape shape(mRadius);
    shape.setFillColor(sf::Color(mFandom[0] LCL_FACTOR, mFandom[1] LCL_FACTOR, mFandom[2] LCL_FACTOR));
    shape.setPosition(position.x, position.y);
    if(drawSprite)
        shape.setTexture(&((*mTextures)[mood]));
    win->draw(shape);
}

bool Besucher::collided(Besucher *besucher)
{
    sf::Vector2f delta = this->position - besucher->position;
    if(delta.x * delta.x + delta.y * delta.y <= (this->mRadius +  besucher->mRadius) * (this->mRadius + besucher->mRadius))
        return true;
    else
        return false;
}

int Besucher::whichIsTheMaxFandom()
{
    float lmax = 0;
    int id;
    for (size_t i = 0; i <= mFandom.size(); ++i) {
        lmax = mFandom[i] > lmax ? id = i, mFandom[i] : lmax;//ich war das nicht !! Das war der da.
    }
    return id;
}

float Besucher::maxFandom()
{
    float lmax = 0;
    for (size_t i = 0; i <= mFandom.size(); ++i) {
        lmax = mFandom[i] > lmax ? mFandom[i] : lmax;
    }
    return lmax;
}

float Besucher::standhaftigkeit()
{
    return (mCharisma < 0 ? 0 : mCharisma) * pow(20, maxFandom());
}

bool Besucher::converge(Besucher *besucher)
{
    int dCharisma = abs(this-> mCharisma - besucher-> mCharisma);
    int dWaveLen  = getWaveDifference(this-> mWavelength, besucher-> mWavelength);
    vecf dFandom  = vec_Sub(&this-> mFandom, &besucher-> mFandom);

    double v[3];
    v[0] = dCharisma / MAX_CHARISMA;
    v[1] = dWaveLen / MAX_DLAMBDA;
    v[2] = vec_Len(&dFandom) / sqrt(dFandom.size() * 4);

    double prop = (v[0] + 1 - v[1] + 1 - v[2]) / 3;
    double r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

    return (r < prop);
}

void besucherCollision(std::shared_ptr<std::vector<Besucher>> besucher)
{
    for(size_t i = 0 ; i < besucher->size(); i++)
    {
        if((*besucher)[i].canInteract() || (*besucher)[i].aggro>= 0)
        {
            for(size_t j = i + 1; j < besucher->size(); j++)
            {
                if((*besucher)[j].canInteract() || (*besucher)[i].aggro >= 0)
                {
                    if((*besucher)[i].collided(&((*besucher)[j])) )
                    {
                        if((*besucher)[i].aggro < 0 && (*besucher)[j].aggro < 0)
                        {
                            vecf dFandom = vec_Mul( vec_Sub( &((*besucher)[i].mFandom), &((*besucher)[j].mFandom) ), 0.4f);
                            float sI = (*besucher)[i].standhaftigkeit();
                            float sJ = (*besucher)[j].standhaftigkeit();
                            if ((*besucher)[i].converge(&((*besucher)[j])) )
                            {
                                (*besucher)[i].mFandom = vec_Sub(&((*besucher)[i].mFandom), vec_Mul( &dFandom, sJ / (sI + sJ)));
                                (*besucher)[j].mFandom = vec_Add( &((*besucher)[j].mFandom), vec_Mul( &dFandom, sI / (sI + sJ)));

                            }
                            else {
                                (*besucher)[i].mFandom = vec_Add(&((*besucher)[i].mFandom), vec_Mul( &dFandom, sJ / (sI + sJ)));
                                (*besucher)[j].mFandom = vec_Sub( &((*besucher)[j].mFandom), vec_Mul( &dFandom, sI / (sI + sJ)));
                            }
                            for(size_t k = 0; k < (*besucher)[i].mFandom.size(); k++)
                            {
                                if((*besucher)[i].mFandom[k] > 1.f)
                                    (*besucher)[i].mFandom[k] = 1.f;
                                else if((*besucher)[i].mFandom[k] < -1.f)
                                    (*besucher)[i].mFandom[k] = -1.f;

                                if((*besucher)[j].mFandom[k] > 1.f)
                                    (*besucher)[j].mFandom[k] = 1.f;
                                else if((*besucher)[j].mFandom[k] < -1.f)
                                    (*besucher)[j].mFandom[k] = -1.f;
                            }

                            (*besucher)[i].interaktionCooldown = IMMUNITY;
                            (*besucher)[j].interaktionCooldown = IMMUNITY;
                        }
                        // Apprallen mit Zufallswinkel
                        sf::Vector2f vecBuffer = (*besucher)[i].movement;
                        (*besucher)[i].movement = rotateVec((*besucher)[j].movement, rand() % REFLECTION_ANGLE - REFLECTION_ANGLE / 2);
                        (*besucher)[j].movement = rotateVec(vecBuffer, rand() % REFLECTION_ANGLE - REFLECTION_ANGLE / 2);


                    }
                }
            }
        }
    }
}

void Besucher::addMerch(size_t units)
{
    mNMerch += units;
}

void Besucher::giveMerch(Besucher *besucher)
{
    if (!besucher || !besucher-> mNMerch) return;

    besucher-> addMerch(1);
    besucher->mFandom[this->whichIsTheMaxFandom()] += MERCH_INC;
    this-> mNMerch -= 1;
}

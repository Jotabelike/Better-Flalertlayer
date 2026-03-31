#include <Geode/Geode.hpp>
#include <Geode/modify/FLAlertLayer.hpp>

using namespace geode::prelude;

template <typename T, typename U>
T exact_cast(U* obj) {
    if (obj && typeid(*obj) == typeid(std::remove_pointer_t<T>)) {
        return static_cast<T>(obj);
    }
    return nullptr;
}

class $modify(CleanAlerts, FLAlertLayer) {
    void show() {
        FLAlertLayer::show();

        if (!exact_cast<FLAlertLayer*>(this)) return;
        if (!this->m_mainLayer) return;

        CCLabelBMFont* titleNode = nullptr;
        CCScale9Sprite* originalBg = nullptr;
        float highestY = -9999.f;
        for (auto child : CCArrayExt<CCNode*>(this->m_mainLayer->getChildren())) {
            if (auto bgBox = typeinfo_cast<CCScale9Sprite*>(child)) {
                originalBg = bgBox;
                bgBox->setVisible(false);
            }
            if (auto label = typeinfo_cast<CCLabelBMFont*>(child)) {
                if (label->getPositionY() > highestY) {
                    highestY = label->getPositionY();
                    titleNode = label;
                }
            }
        }

        if (originalBg) {
            auto bgSize = originalBg->getContentSize();
            auto bgPos = originalBg->getPosition();
            int bgZOrder = originalBg->getZOrder();
            auto customBg = CCScale9Sprite::create("GJ_square04.png");
            customBg->setContentSize(bgSize);
            customBg->setPosition(bgPos);
            customBg->setZOrder(bgZOrder);
            this->m_mainLayer->addChild(customBg);
            float outOffsetX = 0.75f;
            float outOffsetY = 0.75f;
            float leftX = bgPos.x - bgSize.width / 2;
            float rightX = bgPos.x + bgSize.width / 2;
            float topY = bgPos.y + bgSize.height / 2;
            float bottomY = bgPos.y - bgSize.height / 2;
            const char* cornerName = "dailyLevelCorner_001.png";
            int cornerZ = bgZOrder + 1;

            if (auto cornerTL = CCSprite::createWithSpriteFrameName(cornerName)) {
                cornerTL->setAnchorPoint({ 0, 1 });
                cornerTL->setPosition({ leftX - outOffsetX, topY + outOffsetY });
                cornerTL->setFlipY(true);
                cornerTL->setZOrder(cornerZ);
                this->m_mainLayer->addChild(cornerTL);
            }

            if (auto cornerTR = CCSprite::createWithSpriteFrameName(cornerName)) {
                cornerTR->setAnchorPoint({ 1, 1 });
                cornerTR->setPosition({ rightX + outOffsetX, topY + outOffsetY });
                cornerTR->setFlipX(true);
                cornerTR->setFlipY(true);
                cornerTR->setZOrder(cornerZ);
                this->m_mainLayer->addChild(cornerTR);
            }

            if (auto cornerBL = CCSprite::createWithSpriteFrameName(cornerName)) {
                cornerBL->setAnchorPoint({ 0, 0 });
                cornerBL->setPosition({ leftX - outOffsetX, bottomY - outOffsetY });
                cornerBL->setZOrder(cornerZ);
                this->m_mainLayer->addChild(cornerBL);
            }
            if (auto cornerBR = CCSprite::createWithSpriteFrameName(cornerName)) {
                cornerBR->setAnchorPoint({ 1, 0 });
                cornerBR->setPosition({ rightX + outOffsetX, bottomY - outOffsetY });
                cornerBR->setFlipX(true);
                cornerBR->setZOrder(cornerZ);
                this->m_mainLayer->addChild(cornerBR);
            }
        }
       
    }
};
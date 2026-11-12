#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>

using namespace geode::prelude;

// El wave sube al mantener y baja al soltar porque updateJump le pone
// velocidad vertical. Después de que el juego la calcula, la ponemos en 0:
// así el wave avanza recto sin importar los clics.
class $modify(WaveRecto, PlayerObject) {
	void updateJump(float dt) {
		PlayerObject::updateJump(dt);

		if (!m_isDart) return;
		if (!Mod::get()->getSettingValue<bool>("activado")) return;

		m_yVelocity = 0;
	}
};

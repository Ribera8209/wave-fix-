#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>

using namespace geode::prelude;

// Tecla para prender/apagar el mod
$on_mod(Loaded) {
	listenForKeybindSettingPresses("tecla", [](Keybind const&, bool down, bool repeat, double) {
		if (!down || repeat) return false;

		auto mod = Mod::get();
		bool nuevo = !mod->getSettingValue<bool>("activado");
		mod->setSettingValue<bool>("activado", nuevo);

		if (mod->getSettingValue<bool>("aviso")) {
			Notification::create(
				nuevo ? "Wave Recto: ON" : "Wave Recto: OFF",
				nuevo ? NotificationIcon::Success : NotificationIcon::Info
			)->show();
		}
		return false;
	});
}

class $modify(WaveRecto, PlayerObject) {
	void updateJump(float dt) {
		PlayerObject::updateJump(dt);

		if (!m_isDart) return;
		auto mod = Mod::get();
		if (!mod->getSettingValue<bool>("activado")) return;

		auto modo = mod->getSettingValue<std::string>("modo");

		if (modo == "Recto, sube al mantener") {
			// Al soltar el wave baja (velocidad negativa): lo dejamos recto.
			if (m_yVelocity < 0) m_yVelocity = 0;
		}
		else if (modo == "Recto, baja al mantener") {
			// Al mantener el wave sube (velocidad positiva): lo invertimos para que baje.
			// Al soltar baja: lo dejamos recto.
			if (m_yVelocity > 0) m_yVelocity = -m_yVelocity;
			else m_yVelocity = 0;
		}
		else {
			m_yVelocity = 0;
		}
	}
};

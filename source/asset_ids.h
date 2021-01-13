#pragma once

namespace sf
{
	class Texture;
	class Font;
}

enum class TextureID
{
	SFMLLogo
};

enum class FontID
{
	Main,
	Console
};

template <typename Asset, typename Identifier>
class AssetManager;

typedef AssetManager<sf::Texture, TextureID> TextureManager;
typedef AssetManager<sf::Font, FontID> FontManager;

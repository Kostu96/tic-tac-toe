#pragma once
#include <memory>
#include <map>
#include <cassert>
#include <stdexcept>
#include <string>

template <typename Asset, typename Identifier>
class AssetManager
{
private:
	std::map<Identifier, std::unique_ptr<Asset>> m_assetMap;
public:
	void load(Identifier id, const std::string & filename);
	template <typename Parameter>
	void load(Identifier id, const std::string & filename, const Parameter & secondParam);
	Asset & get(Identifier id);
	const Asset & get(Identifier id) const;
};

template<typename Asset, typename Identifier>
void AssetManager<Asset, Identifier>::load(Identifier id, const std::string & filename)
{
	std::unique_ptr<Asset> asset(new Asset());
	if (!asset->loadFromFile(filename))
		throw std::runtime_error("Failed to load " + filename);
	auto inserted = m_assetMap.insert(std::make_pair(id, std::move(asset)));
	assert(inserted.second);
}

template<typename Asset, typename Identifier>
template<typename Parameter>
void AssetManager<Asset, Identifier>::load(Identifier id, const std::string & filename, const Parameter & secondParam)
{
	std::unique_ptr<Asset> asset(new Asset());
	if (!asset->loadFromFile(filename, secondParam))
		throw std::runtime_error("Failed to load " + filename);
	auto inserted = m_assetMap.insert(std::make_pair(id, std::move(asset)));
	assert(inserted.second);
}

template<typename Asset, typename Identifier>
Asset & AssetManager<Asset, Identifier>::get(Identifier id)
{
	auto found = m_assetMap.find(id);
	assert(found != m_assetMap.end());
	return *found->second;
}

template<typename Asset, typename Identifier>
const Asset & AssetManager<Asset, Identifier>::get(Identifier id) const
{
	auto found = m_assetMap.find(id);
	assert(found != m_assetMap.end());
	return *found->second;
}

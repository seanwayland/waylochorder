void saveToXml(File dest, std::vector<std::vector<int>> src)
{
	if (dest.exists())
		dest.deleteFile();
	XmlElement chordselem("chords");
	for (int i=0;i<src.size();++i)
	{
		XmlElement* chordelem = chordselem.createNewChildElement("chord_"+String(i));
		for (int j = 0; j < src[i].size(); ++j)
		{
			chordelem->setAttribute("note_"+String(j), src[i][j]);
		}
	}
	chordselem.writeToFile(dest, "");
}

std::vector<std::vector<int>> readFromXml(File src)
{
	std::vector<std::vector<int>> result;
	auto xml = juce::parseXML(src);
	int numchildren = xml->getNumChildElements();
	result.resize(numchildren);
	for (int i = 0; i < numchildren; ++i)
	{
		auto chordelem = xml->getChildElement(i);
		int numnotes = chordelem->getNumAttributes();
		result[i].resize(numnotes);
		for (int j = 0; j < chordelem->getNumAttributes(); ++j)
		{
			result[i][j] = chordelem->getAttributeValue(j).getIntValue();
		}
	}
	return result;
}

ValueTree makeChordValueTree(String name, std::initializer_list<int> notes)
{
    ValueTree result(name);
    for (size_t i=0;i<notes.size();++i)
        result.setProperty("note_"+String(i), *(notes.begin()+i), nullptr);
    return result;
}

ValueTree vt("chords");
vt.addChild(makeChordValueTree("Cmaj", {60,64,67}), -1, nullptr);
vt.addChild(makeChordValueTree("Cmin", {60,63,67}), -1, nullptr);
std::unique_ptr<XmlElement> xml(vt.createXml());
xml->writeToFile(File("/Users/name/chords1.xml"), "");




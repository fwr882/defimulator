#ifdef SYSTEM_CPP

serializer System::serialize()
{
    serializer s(serialize_size);

    unsigned signature = 0x31545342;
    unsigned version = Info::SerializerVersion;
    unsigned crc32 = 0;

    char description[512];
    memset(&description, 0, sizeof description);

    s.integer(signature);
    s.integer(version);
    s.integer(crc32);
    s.array(description);

    serialize_all(s);
    return s;
}

bool System::unserialize(serializer &s)
{
    unsigned signature;
    unsigned version;
    unsigned crc32;
    char description[512];

    s.integer(signature);
    s.integer(version);
    s.integer(crc32);
    s.array(description);

    if (signature != 0x31545342) {
        return false;
    }

    if (version != Info::SerializerVersion) {
        return false;
    }

//if(crc32 != 0) return false;

    serialize_all(s);
    return true;
}

void System::serialize(serializer &s)
{
    s.integer(clocks_executed);
}

void System::serialize_all(serializer &s)
{
    cartridge.serialize(s);
    system.serialize(s);
    cpu.serialize(s);
    lcd.serialize(s);
}

void System::serialize_init(void)
{
    serializer s;

    unsigned signature = 0;
    unsigned version = 0;
    unsigned crc32 = 0;
    char description[512];

    s.integer(signature);
    s.integer(version);
    s.integer(crc32);
    s.array(description);

    serialize_all(s);
    serialize_size = s.size();
}

#endif

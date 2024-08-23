#include <gtest/gtest.h>

#include <librotate.h>

#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <fstream>
#include <bitset>
#include <cstdio>

class ArrayBuff : Base {
public:
    virtual ~ArrayBuff() {
        delete [] m_out;
    }

    ArrayBuff(uint8_t * ar, unsigned int size) : 
        m_arr(ar),
        m_out(new uint8_t[size]),
        m_size(size),
        m_place(0) {}

    virtual void init() {
        m_place = 0;
        m_out_place = 0;
    }

    virtual uint8_t get_next_byte() {
        if(m_place < m_size) {
            return m_arr[m_place++];
        }  else {
            std::cerr << "Out of bounds" << std::endl; 
            abort();
        }
    } 
    
    virtual void write_next_byte(uint8_t byte) {
        m_out[m_out_place++] = byte;
    };

    virtual unsigned int get_length() {
        return m_size;
    }

    virtual void rotate_left() {
        Base::rotate_left();
    }

    virtual void rotate_right() {
        Base::rotate_right();
    }

    virtual bool end() {
        return m_place == m_size;
    }

    uint8_t get_rotate_byte() {
        return m_out[m_out_place++];
    }

private:
    uint8_t * m_arr;
    uint8_t * m_out;
    unsigned int m_size;
    unsigned int m_place;
    unsigned int m_out_place;
};


TEST(testBuffer,tetsBasicBitShift) {
    uint8_t bit = 128;       // 0xb10000000
    uint8_t bit2 = bit >> 7; // 0xb00000001

    ASSERT_EQ(bit2,1);

    bit2 = bit2 << 7;

    ASSERT_EQ(bit2,bit);

}

TEST(testBuffer,testRotateLeftOnSimpleArray) {
    uint8_t bytes[] = {146, 146, 146};

    ArrayBuff b(bytes,3);
    b.init();

    b.rotate_left();
    b.init();

    
    ASSERT_EQ((uint8_t)37,b.get_rotate_byte());
    ASSERT_EQ((uint8_t)37,b.get_rotate_byte());
    ASSERT_EQ((uint8_t)37,b.get_rotate_byte());
 
}

TEST(testBuffer,testRotateLeftOnSingleByte) {
    uint8_t bytes[] = {146};

    ArrayBuff b(bytes,1);
    b.init();

    b.rotate_left();
    b.init();

    ASSERT_EQ((uint8_t)37,b.get_rotate_byte()); 
}

TEST(testBuffer,testRotateLeftOnMultyByte) {
    uint8_t bytes[] = {146, 146, 146, 146, 146};

    ArrayBuff b(bytes,5);
    b.init();

    b.rotate_left();
    b.init();

    
    ASSERT_EQ((uint8_t)37,b.get_rotate_byte()); 
    ASSERT_EQ((uint8_t)37,b.get_rotate_byte()); 
    ASSERT_EQ((uint8_t)37,b.get_rotate_byte()); 
    ASSERT_EQ((uint8_t)37,b.get_rotate_byte()); 
    ASSERT_EQ((uint8_t)37,b.get_rotate_byte()); 
}

TEST(testBuffer,testRotateLeftComplpexArray) {
    uint8_t bytes[] = {146, 147, 148, 149, 150};

    ArrayBuff b(bytes,5);
    b.init();

    b.rotate_left();
    b.init();

    
    ASSERT_EQ((uint8_t)37,b.get_rotate_byte());  
    ASSERT_EQ((uint8_t)39,b.get_rotate_byte()); 
    ASSERT_EQ((uint8_t)41,b.get_rotate_byte()); 
    ASSERT_EQ((uint8_t)43,b.get_rotate_byte()); 
    ASSERT_EQ((uint8_t)45,b.get_rotate_byte()); 
}

TEST(testBuffer,testRotateLeftWithFiles) {
    uint8_t bytes[] = {146, 147, 148, 149, 150};

    std::ofstream of;
    
    of.open("test.bin",std::ios::binary | std::ios::out);

    for(int i=0;i<5;i++) {
        of.write((char*)&bytes[i],1);
    }

    of.close();

    Buffer  * b = new Buffer("test.bin","out.bin");
    b->init();
    b->rotate_left();
    delete b;

    std::ifstream in;
    in.open("out.bin",std::ios::binary |  std::ios::in);
    in.seekg(0, in.end);
    int length = in.tellg();
    in.seekg(0, in.beg);

    ASSERT_EQ(5,length);


    uint8_t data;

    in.read((char*)&data,1);
    ASSERT_EQ((uint8_t)37,data);
    in.read((char*)&data,1);  
    ASSERT_EQ((uint8_t)39,data);
    in.read((char*)&data,1); 
    ASSERT_EQ((uint8_t)41,data);
    in.read((char*)&data,1); 
    ASSERT_EQ((uint8_t)43,data);
    in.read((char*)&data,1); 
    ASSERT_EQ((uint8_t)45,data); 

    std::remove("test.bin");
    std::remove("out.bin");
}

TEST(testBuffer,testRotateLeftWithFilesAndComplexBitPatterns) {
    uint8_t bytes[] = {204, 61, 206, 9, 141};

    std::ofstream of;
    
    of.open("test.bin",std::ios::binary | std::ios::out);

    for(int i=0;i<5;i++) {
        of.write((char*)&bytes[i],1);
    }

    of.close();

    Buffer  * b = new Buffer("test.bin","out.bin");
    b->init();
    b->rotate_left();
    delete b;

    std::ifstream in;
    in.open("out.bin",std::ios::binary |  std::ios::in);
    in.seekg(0, in.end);
    int length = in.tellg();
    in.seekg(0, in.beg);

    ASSERT_EQ(5,length);

    uint8_t data;

    in.read((char*)&data,1);
    ASSERT_EQ((uint8_t)152,data);
    in.read((char*)&data,1);  
    ASSERT_EQ((uint8_t)123,data);
    in.read((char*)&data,1); 
    ASSERT_EQ((uint8_t)156,data);
    in.read((char*)&data,1); 
    ASSERT_EQ((uint8_t)19,data);
    in.read((char*)&data,1); 
    ASSERT_EQ((uint8_t)27,data); 

    std::remove("test.bin");
    std::remove("out.bin");
}

TEST(testBuffer,testRotateRightOnSimpleArray) {
    uint8_t bytes[] = {146, 146, 146};

    ArrayBuff b(bytes,3);
    b.init();

    b.rotate_right();
    b.init();

    
    ASSERT_EQ((uint8_t)73,b.get_rotate_byte());
    ASSERT_EQ((uint8_t)73,b.get_rotate_byte());
    ASSERT_EQ((uint8_t)73,b.get_rotate_byte());
 
}

TEST(testBuffer,testRotateRightOnSingleByte) {
    uint8_t bytes[] = {146};

    ArrayBuff b(bytes,1);
    b.init();

    b.rotate_right();
    b.init();

    ASSERT_EQ((uint8_t)73,b.get_rotate_byte()); 
}

TEST(testBuffer,testRotateRightComplpexArray) {
    uint8_t bytes[] = {146, 147, 148, 149, 150};

    ArrayBuff b(bytes,5);
    b.init();

    b.rotate_right();
    b.init();

    
    ASSERT_EQ((uint8_t)73,b.get_rotate_byte());  
    ASSERT_EQ((uint8_t)73,b.get_rotate_byte()); 
    ASSERT_EQ((uint8_t)202,b.get_rotate_byte()); 
    ASSERT_EQ((uint8_t)74,b.get_rotate_byte()); 
    ASSERT_EQ((uint8_t)203,b.get_rotate_byte()); 
}

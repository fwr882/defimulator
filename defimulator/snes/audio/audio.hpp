class Audio {
public:
    void coprocessor_enable(bool state);
    void coprocessor_frequency(double frequency);
    void sample(int16 left, int16 right);
    void coprocessor_sample(int16 left, int16 right);
    void init(void);

private:
    bool coprocessor;

    uint32 dsp_buffer[32768];
    uint32 cop_buffer[32768];

    unsigned dsp_rdoffset;
    unsigned cop_rdoffset;

    unsigned dsp_wroffset;
    unsigned cop_wroffset;

    unsigned dsp_length;
    unsigned cop_length;

    double r_step;
    double r_frac;
    int r_sum_l;
    int r_sum_r;

    void flush(void);
};

extern Audio audio;

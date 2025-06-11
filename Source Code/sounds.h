#include "includes.h"

namespace Sounds
{
    void audio0() {
        HWAVEOUT hWaveOut = 0;
        WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 10000, 10000, 1, 8, 0 };
        waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
        char buffer[10000 * 60] = {};
        
        for (DWORD t = 0; t < sizeof(buffer); t++) {
            buffer[t] = t*sinf((t/7 >> 3 | t/10000));
        }

        WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
        waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
        waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
        waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
        waveOutClose(hWaveOut);
    }

    void audio1() {
        HWAVEOUT hWaveOut = 0;
        WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 10000, 10000, 1, 8, 0 };
        waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
        char buffer[10000 * 35] = {};
        
        for (DWORD t = 0; t < sizeof(buffer); t++) {
            buffer[t] = t*sinf((t/3 >> 3 | t/10000));
        }

        WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
        waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
        waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
        waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
        waveOutClose(hWaveOut);
    }

    void audio2() {
        HWAVEOUT hWaveOut = 0;
        WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
        waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
        char buffer[8000 * 35] = {};
        
        for (DWORD t = 0; t < sizeof(buffer); t++) {
            buffer[t] = t*(t >> 3 | t/1000);
        }

        WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
        waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
        waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
        waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
        waveOutClose(hWaveOut);
    }

    void audio3() {
        HWAVEOUT hWaveOut = 0;
        WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
        waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
        char buffer[8000 * 35] = {};
        
        for (DWORD t = 0; t < sizeof(buffer); t++) {
            buffer[t] = t*(t * 2 ^ t/1000);
        }

        WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
        waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
        waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
        waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
        waveOutClose(hWaveOut);
    }

    void audio4() {
        HWAVEOUT hWaveOut = 0;
        WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
        waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
        char buffer[8000 * 35] = {};
        
        for (DWORD t = 0; t < sizeof(buffer); t++) {
            buffer[t] = 10*sinf(t/1000 | t);
        }

        WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
        waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
        waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
        waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
        waveOutClose(hWaveOut);
    }

    void audio5() {
        HWAVEOUT hWaveOut = 0;
        WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11000, 11000, 1, 8, 0 };
        waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
        char buffer[11000 * 35] = {};
        
        for (DWORD t = 0; t < sizeof(buffer); t++) {
            buffer[t] = 55 * (t/7 & t/1000);
        }

        WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
        waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
        waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
        waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
        waveOutClose(hWaveOut);
    }

    void audio6() {
        HWAVEOUT hWaveOut = 0;
        WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11000, 11000, 1, 8, 0 };
        waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
        char buffer[11000 * 50] = {};
        
        for (DWORD t = 0; t < sizeof(buffer); t++) {
            buffer[t] = (t/2/(4+(t>>13&3))*128|t>>(t>>12&15))+400000/((t&4095)+1)*4;
        }

        WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
        waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
        waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
        waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
        waveOutClose(hWaveOut);
    }
    
    void audio7() {
        HWAVEOUT hWaveOut = 0;
        WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
        waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
        char buffer[8000 * 35] = {};
        
        for (DWORD t = 0; t < sizeof(buffer); t++) {
            buffer[t] = (t>>7|t|t>>6)*t;
        }

        WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
        waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
        waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
        waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
        waveOutClose(hWaveOut);
    }
    
    void audio8() {
        HWAVEOUT hWaveOut = 0;
        WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
        waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
        char buffer[8000 * 35] = {};
        
        for (DWORD t = 0; t < sizeof(buffer); t++) {
            buffer[t] = 55 * sin(t/2 ^ t/1000);
        }

        WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
        waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
        waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
        waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
        waveOutClose(hWaveOut);
    }

    void audio9() {
        HWAVEOUT hWaveOut = 0;
        WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
        waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
        char buffer[8000 * 45] = {};
        
        for (DWORD t = 0; t < sizeof(buffer); t++) {
            buffer[t] = (t%25-(t>>2|15*t|t%227)*t)*2;
        }

        WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
        waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
        waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
        waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
        waveOutClose(hWaveOut);
    }

    void audio10() {
        HWAVEOUT hWaveOut = 0;
        WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11000, 11000, 1, 8, 0 };
        waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
        char buffer[11000 * 30] = {};
        
        for (DWORD t = 0; t < sizeof(buffer); t++) {
            buffer[t] = t*rand() << t*rand();
        }

        WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
        waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
        waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
        waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
        waveOutClose(hWaveOut);
    }
}
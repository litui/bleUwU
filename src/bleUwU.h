

namespace bleuwu {

#define SELKIRK_3G_APP_ID 0

static const char *TAG = "bleUwU";

static const char *DEVICE_LOCAL_NAME ="YOWU-SELKIRK-3G";
static const char *SERVICE_UUID = "00001802-0000-1000-8000-00805f9b34fb";
static const char *SELKIRK_UUID = "00002a06-0000-1000-8000-00805f9b34fb";

class Selkirk3G {
    public:
        Selkirk3G();

        void init(void);
        void begin_scan(void);
    
};

} // Namespace nyowulib
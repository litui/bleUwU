#include "nvs.h"
#include "nvs_flash.h"
#include "esp_bt.h"
#include "esp_gap_ble_api.h"
#include "esp_gattc_api.h"
#include "esp_gatt_defs.h"
#include "esp_bt_main.h"
#include "esp_gatt_common_api.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "bleuwu.h"

namespace bleuwu {

Selkirk3G::Selkirk3G() {
}

void init(void) {
    // Initialize NVS.
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );

    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    ret = esp_bt_controller_init(&bt_cfg);

    if (ret) {
        ESP_LOGE(TAG, "%s initialize controller failed, error code = %x\n", __func__, ret);
        return;
    }

    ret = esp_bt_controller_enable(ESP_BT_MODE_BLE);
    if (ret) {
        ESP_LOGE(TAG, "%s enable controller failed, error code = %x\n", __func__, ret);
        return;
    }

    ret = esp_bluedroid_init();
    if (ret) {
        ESP_LOGE(TAG, "%s init bluetooth failed, error code = %x\n", __func__, ret);
        return;
    }

    ret = esp_bluedroid_enable();
    if (ret) {
        ESP_LOGE(TAG, "%s enable bluetooth failed, error code = %x\n", __func__, ret);
        return;
    }

    // //register the  callback function to the gap module
    // ret = esp_ble_gap_register_callback(gap_register_cb);
    // if (ret){
    //     ESP_LOGE(TAG, "%s gap register failed, error code = %x\n", __func__, ret);
    //     return;
    // }

    // //register the callback function to the gattc module
    // ret = esp_ble_gattc_register_callback(gattc_register_cb);
    // if(ret){
    //     ESP_LOGE(TAG, "%s gattc register failed, error code = %x\n", __func__, ret);
    //     return;
    // }

    ret = esp_ble_gattc_app_register(SELKIRK_3G_APP_ID);
    if (ret){
        ESP_LOGE(TAG, "%s gattc app register failed, error code = %x\n", __func__, ret);
    }

    esp_err_t local_mtu_ret = esp_ble_gatt_set_local_mtu(500);
    if (local_mtu_ret){
        ESP_LOGE(TAG, "set local  MTU failed, error code = %x", local_mtu_ret);
    }
}

void begin_scan(void) {

}

// BLERemoteService* pRemoteService = pClient->getService(yowu_service_uuid);
// if (pRemoteService == nullptr) {
//     tft.print("Could not locate service: ");
//     tft.println(yowu_service_uuid.toString().c_str());
//     pClient->disconnect();
//     return false;
// }

// tft.println("Between remote service location and char location.");

// uint16_t charCount = 2;
// uint16_t *ccPtr = &charCount;
// esp_gattc_char_elem_t *result = (esp_gattc_char_elem_t*) calloc(charCount+1, sizeof(esp_gattc_char_elem_t));
// for (int i = 0; i<charCount+1; i++) {
//     result[i] = esp_gattc_char_elem_t();
// }
// esp_bt_uuid_t native_uuid = *yowu_secret_uuid.getNative();
// int err = esp_ble_gattc_get_char_by_uuid(pClient->getGattcIf(),
//                                         pClient->getConnId(),
//                                         0,
//                                         32767,
//                                         native_uuid,
//                                         result,
//                                         ccPtr);
// tft.printf("Get Char result: %d\n", err);

} // namespace nyowulib
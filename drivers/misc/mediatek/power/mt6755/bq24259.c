#include <linux/types.h>
#include <linux/init.h>		/* For init/exit macros */
#include <linux/module.h>	/* For MODULE_ marcros  */
#include <linux/platform_device.h>
#include <linux/i2c.h>
#include <linux/slab.h>
#ifdef CONFIG_OF
#include <linux/of.h>
#include <linux/of_irq.h>
#include <linux/of_address.h>
#endif
#include <mt-plat/charging.h>
#include "bq24259.h"

//lenovo-sw mahj2 add for board temp Begin
#include <linux/power_supply.h>
//#include <mach/mt_thermal.h>
//lenovo-sw mahj2 add for board temp End
/**********************************************************
  *
  *   [I2C Slave Setting]
  *
  *********************************************************/
#define bq24259_SLAVE_ADDR_WRITE   0xD6
#define bq24259_SLAVE_ADDR_READ    0xD7

//lenovo-sw mahj2 modify at 20150318 Begin
#define bq24259_BUSNUM 1
//lenovo-sw mahj2 modify at 20150318 End
//lenovo-sw mahj2 add for board temp Begin
#define bq24259_POWER_SUPPLY
#ifdef bq24259_POWER_SUPPLY
	struct power_supply charger;
extern int mtkts_bts_get_hw_temp(void);
#endif
//lenovo-sw mahj2 add for board temp End
static struct i2c_client *new_client = NULL;
static const struct i2c_device_id bq24259_i2c_id[] = { {"bq24259", 0}, {} };

kal_bool chargin_hw_init_done = KAL_FALSE;
static int bq24259_driver_probe(struct i2c_client *client, const struct i2c_device_id *id);

//lenovo-sw mahj2 add for board temp Begin
#ifdef bq24259_POWER_SUPPLY

static enum power_supply_property bq24259_power_supply_props[] = {
	/* TODO: maybe add more power supply properties */
	POWER_SUPPLY_PROP_TEMP,
};

static int bq24259_power_supply_get_property(struct power_supply *psy,
					     enum power_supply_property psp,
					     union power_supply_propval *val)
{
	switch (psp) {
	case POWER_SUPPLY_PROP_TEMP:
		val->intval = mtkts_bts_get_hw_temp()/1000;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}

static int bq24259_power_supply_set_property(struct power_supply *psy,
					     enum power_supply_property psp,
					     const union power_supply_propval *val)
{
	switch (psp) {
		default:
			pr_err("%s not support power_supply property cmd\n", __func__);
			return -EINVAL;
	}
	return 0;
}

static int bq24259_power_supply_property_is_writeable(struct power_supply *psy,
					enum power_supply_property psp)
{
	switch (psp) {
		default:
			break;
	}

	return 0;
}

static int bq24259_power_supply_init(struct i2c_client *client)
{
	int ret;

	charger.name = "ext-charger";
	charger.type = POWER_SUPPLY_TYPE_USB;
	charger.properties = bq24259_power_supply_props;
	charger.num_properties = ARRAY_SIZE(bq24259_power_supply_props);
	charger.get_property = bq24259_power_supply_get_property;
	charger.set_property = bq24259_power_supply_set_property;
	charger.property_is_writeable = bq24259_power_supply_property_is_writeable;	

	ret = power_supply_register(&client->dev, &charger);
	if (ret) {
		return -1;
	}

	return 0;
}

#endif
//lenovo-sw mahj2 add for board temp End

#ifdef CONFIG_OF
static const struct of_device_id bq24259_of_match[] = {
	{.compatible = "mediatek,SWITHING_CHARGER"},
	{},
};
#else
//lenovo-sw mahj2 modify at 20150318 Begin
static struct i2c_board_info __initdata i2c_bq24259 = { I2C_BOARD_INFO("bq24259", (bq24259_SLAVE_ADDR_WRITE>>1))};
//lenovo-sw mahj2 modify at 20150318 End
#endif
static void bq24259_shutdown(struct i2c_client *client)
{

    printk("[bq24259_shutdown] driver shutdown \n");
    bq24259_set_chg_config(0x0);
	//lenovo-sw mahj2 modify for shutdown but OTG vbus enable,Begin
	bq24259_set_otg_config(0x0);
	//lenovo-sw mahj2 modify for shutdown but OTG vbus enable,End
}

static struct i2c_driver bq24259_driver = {
	.driver = {
		   .name = "bq24259",
#ifdef CONFIG_OF
		   .of_match_table = bq24259_of_match,
#endif
		   },
	.probe = bq24259_driver_probe,
	.id_table = bq24259_i2c_id,
    .shutdown    = bq24259_shutdown,
};

/**********************************************************
  *
  *   [Global Variable]
  *
  *********************************************************/
unsigned char bq24259_reg[bq24259_REG_NUM] = { 0 };

static DEFINE_MUTEX(bq24259_i2c_access);

int g_bq24259_hw_exist = 0;

/**********************************************************
  *
  *   [I2C Function For Read/Write bq24259]
  *
  *********************************************************/
int bq24259_read_byte(unsigned char cmd, unsigned char *returnData)
{
	char cmd_buf[1] = { 0x00 };
	char readData = 0;
	int ret = 0;

	mutex_lock(&bq24259_i2c_access);

	/* new_client->addr = ((new_client->addr) & I2C_MASK_FLAG) | I2C_WR_FLAG; */
	new_client->ext_flag =
	    ((new_client->ext_flag) & I2C_MASK_FLAG) | I2C_WR_FLAG | I2C_DIRECTION_FLAG;

	cmd_buf[0] = cmd;
	ret = i2c_master_send(new_client, &cmd_buf[0], (1 << 8 | 1));
	if (ret < 0) {
		/* new_client->addr = new_client->addr & I2C_MASK_FLAG; */
		new_client->ext_flag = 0;

		mutex_unlock(&bq24259_i2c_access);
	//lenovo-sw mahj2 add for debug at 20150318 Begin
	printk("bq24259 i2c read byte error: %d\n",ret);
	//lenovo-sw mahj2 add for debug at 20150318 End
		return 0;
	}

	readData = cmd_buf[0];
	*returnData = readData;

	/* new_client->addr = new_client->addr & I2C_MASK_FLAG; */
	new_client->ext_flag = 0;

	mutex_unlock(&bq24259_i2c_access);
	return 1;
}

int bq24259_write_byte(unsigned char cmd, unsigned char writeData)
{
	char write_data[2] = { 0 };
	int ret = 0;

	mutex_lock(&bq24259_i2c_access);

	write_data[0] = cmd;
	write_data[1] = writeData;

	new_client->ext_flag = ((new_client->ext_flag) & I2C_MASK_FLAG) | I2C_DIRECTION_FLAG;

	ret = i2c_master_send(new_client, write_data, 2);
	if (ret < 0) {
		new_client->ext_flag = 0;
		mutex_unlock(&bq24259_i2c_access);
	//lenovo-sw mahj2 add for debug at 20150318 Begin
	printk("bq24259 i2c write byte error: %d\n",ret);
	//lenovo-sw mahj2 add for debug at 20150318 End
		return 0;
	}

	new_client->ext_flag = 0;
	mutex_unlock(&bq24259_i2c_access);
	return 1;
}

/**********************************************************
  *
  *   [Read / Write Function]
  *
  *********************************************************/
unsigned int bq24259_read_interface(unsigned char RegNum, unsigned char *val, unsigned char MASK,
				  unsigned char SHIFT)
{
	unsigned char bq24259_reg = 0;
	int ret = 0;

	battery_log(BAT_LOG_FULL, "--------------------------------------------------\n");

	ret = bq24259_read_byte(RegNum, &bq24259_reg);

	battery_log(BAT_LOG_FULL, "[bq24259_read_interface] Reg[%x]=0x%x\n", RegNum, bq24259_reg);

	bq24259_reg &= (MASK << SHIFT);
	*val = (bq24259_reg >> SHIFT);

	battery_log(BAT_LOG_FULL, "[bq24259_read_interface] val=0x%x\n", *val);

	return ret;
}

unsigned int bq24259_config_interface(unsigned char RegNum, unsigned char val, unsigned char MASK,
				    unsigned char SHIFT)
{
	unsigned char bq24259_reg = 0;
	int ret = 0;

	battery_log(BAT_LOG_FULL, "--------------------------------------------------\n");

	ret = bq24259_read_byte(RegNum, &bq24259_reg);
	battery_log(BAT_LOG_FULL, "[bq24259_config_interface] Reg[%x]=0x%x\n", RegNum, bq24259_reg);

	bq24259_reg &= ~(MASK << SHIFT);
	bq24259_reg |= (val << SHIFT);

	ret = bq24259_write_byte(RegNum, bq24259_reg);
	battery_log(BAT_LOG_FULL, "[bq24259_config_interface] write Reg[%x]=0x%x\n", RegNum, bq24259_reg);

	/* Check */
	/* bq24259_read_byte(RegNum, &bq24259_reg); */
	/* battery_log(BAT_LOG_FULL, "[bq24259_config_interface] Check Reg[%x]=0x%x\n", RegNum, bq24259_reg); */

	return ret;
}

/* write one register directly */
unsigned int bq24259_reg_config_interface(unsigned char RegNum, unsigned char val)
{
	unsigned int ret = 0;

	ret = bq24259_write_byte(RegNum, val);

	return ret;
}

/**********************************************************
  *
  *   [Internal Function]
  *
  *********************************************************/
/* CON0---------------------------------------------------- */

void bq24259_set_en_hiz(unsigned int val)
{
	unsigned int ret = 0;

	ret = bq24259_config_interface((unsigned char) (bq24259_CON0),
				       (unsigned char) (val),
				       (unsigned char) (CON0_EN_HIZ_MASK),
				       (unsigned char) (CON0_EN_HIZ_SHIFT)
	    );
}

void bq24259_set_vindpm(unsigned int val)
{
	unsigned int ret = 0;

	ret = bq24259_config_interface((unsigned char) (bq24259_CON0),
				       (unsigned char) (val),
				       (unsigned char) (CON0_VINDPM_MASK),
				       (unsigned char) (CON0_VINDPM_SHIFT)
	    );
}

void bq24259_set_iinlim(unsigned int val)
{
	unsigned int ret = 0;

	ret = bq24259_config_interface((unsigned char) (bq24259_CON0),
				       (unsigned char) (val),
				       (unsigned char) (CON0_IINLIM_MASK),
				       (unsigned char) (CON0_IINLIM_SHIFT)
	    );
}

/* CON1---------------------------------------------------- */

void bq24259_set_reg_rst(unsigned int val)
{
	unsigned int ret = 0;

	ret = bq24259_config_interface((unsigned char) (bq24259_CON1),
				       (unsigned char) (val),
				       (unsigned char) (CON1_REG_RST_MASK),
				       (unsigned char) (CON1_REG_RST_SHIFT)
	    );
}

void bq24259_set_wdt_rst(unsigned int val)
{
	unsigned int ret = 0;

	ret = bq24259_config_interface((unsigned char) (bq24259_CON1),
				       (unsigned char) (val),
				       (unsigned char) (CON1_WDT_RST_MASK),
				       (unsigned char) (CON1_WDT_RST_SHIFT)
	    );
}

void bq24259_set_otg_config(unsigned int val)
{
	unsigned int ret = 0;

	ret = bq24259_config_interface((unsigned char) (bq24259_CON1),
				       (unsigned char) (val),
				       (unsigned char) (CON1_OTG_CONFIG_MASK),
				       (unsigned char) (CON1_OTG_CONFIG_SHIFT)
	    );
}

void bq24259_set_chg_config(unsigned int val)
{
	unsigned int ret = 0;

	ret = bq24259_config_interface((unsigned char) (bq24259_CON1),
				       (unsigned char) (val),
				       (unsigned char) (CON1_CHG_CONFIG_MASK),
				       (unsigned char) (CON1_CHG_CONFIG_SHIFT)
	    );
}

void bq24259_set_sys_min(unsigned int val)
{
	unsigned int ret = 0;

	ret = bq24259_config_interface((unsigned char) (bq24259_CON1),
				       (unsigned char) (val),
				       (unsigned char) (CON1_SYS_MIN_MASK),
				       (unsigned char) (CON1_SYS_MIN_SHIFT)
	    );
}

void bq24259_set_boost_lim(unsigned int val)
{
	unsigned int ret = 0;

	ret = bq24259_config_interface((unsigned char) (bq24259_CON1),
				       (unsigned char) (val),
				       (unsigned char) (CON1_BOOST_LIM_MASK),
				       (unsigned char) (CON1_BOOST_LIM_SHIFT)
	    );
}

/* CON2---------------------------------------------------- */

void bq24259_set_ichg(unsigned int val)
{
	unsigned int ret = 0;

	ret = bq24259_config_interface((unsigned char) (bq24259_CON2),
				       (unsigned char) (val),
				       (unsigned char) (CON2_ICHG_MASK), (unsigned char) (CON2_ICHG_SHIFT)
	    );
}

void bq24259_set_bcold(unsigned int val)
{
	unsigned int ret = 0;

	ret = bq24259_config_interface((unsigned char) (bq24259_CON2),
				       (unsigned char) (val),
				       (unsigned char) (CON2_BCOLD_MASK), (unsigned char) (CON2_BCOLD_SHIFT)
	    );
}

void bq24259_set_force_20pct(unsigned int val)
{
	unsigned int ret = 0;

	ret = bq24259_config_interface((unsigned char) (bq24259_CON2),
				       (unsigned char) (val),
				       (unsigned char) (CON2_FORCE_20PCT_MASK),
				       (unsigned char) (CON2_FORCE_20PCT_SHIFT)
	    );
}

/* CON3---------------------------------------------------- */

void bq24259_set_iprechg(unsigned int val)
{
	unsigned int ret = 0;

	ret = bq24259_config_interface((unsigned char) (bq24259_CON3),
				       (unsigned char) (val),
				       (unsigned char) (CON3_IPRECHG_MASK),
				       (unsigned char) (CON3_IPRECHG_SHIFT)
	    );
}

void bq24259_set_iterm(unsigned int val)
{
	unsigned int ret = 0;

	ret = bq24259_config_interface((unsigned char) (bq24259_CON3),
				       (unsigned char) (val),
				       (unsigned char) (CON3_ITERM_MASK), (unsigned char) (CON3_ITERM_SHIFT)
	    );
}

/* CON4---------------------------------------------------- */

void bq24259_set_vreg(unsigned int val)
{
	unsigned int ret = 0;

	ret = bq24259_config_interface((unsigned char) (bq24259_CON4),
				       (unsigned char) (val),
				       (unsigned char) (CON4_VREG_MASK), (unsigned char) (CON4_VREG_SHIFT)
	    );
}

void bq24259_set_batlowv(unsigned int val)
{
	unsigned int ret = 0;

	ret = bq24259_config_interface((unsigned char) (bq24259_CON4),
				       (unsigned char) (val),
				       (unsigned char) (CON4_BATLOWV_MASK),
				       (unsigned char) (CON4_BATLOWV_SHIFT)
	    );
}

void bq24259_set_vrechg(unsigned int val)
{
	unsigned int ret = 0;

	ret = bq24259_config_interface((unsigned char) (bq24259_CON4),
				       (unsigned char) (val),
				       (unsigned char) (CON4_VRECHG_MASK),
				       (unsigned char) (CON4_VRECHG_SHIFT)
	    );
}

/* CON5---------------------------------------------------- */

void bq24259_set_en_term(unsigned int val)
{
	unsigned int ret = 0;

	ret = bq24259_config_interface((unsigned char) (bq24259_CON5),
				       (unsigned char) (val),
				       (unsigned char) (CON5_EN_TERM_MASK),
				       (unsigned char) (CON5_EN_TERM_SHIFT)
	    );
}

void bq24259_set_watchdog(unsigned int val)
{
	unsigned int ret = 0;

	ret = bq24259_config_interface((unsigned char) (bq24259_CON5),
				       (unsigned char) (val),
				       (unsigned char) (CON5_WATCHDOG_MASK),
				       (unsigned char) (CON5_WATCHDOG_SHIFT)
	    );
}

void bq24259_set_en_timer(unsigned int val)
{
	unsigned int ret = 0;

	ret = bq24259_config_interface((unsigned char) (bq24259_CON5),
				       (unsigned char) (val),
				       (unsigned char) (CON5_EN_TIMER_MASK),
				       (unsigned char) (CON5_EN_TIMER_SHIFT)
	    );
}

void bq24259_set_chg_timer(unsigned int val)
{
	unsigned int ret = 0;

	ret = bq24259_config_interface((unsigned char) (bq24259_CON5),
				       (unsigned char) (val),
				       (unsigned char) (CON5_CHG_TIMER_MASK),
				       (unsigned char) (CON5_CHG_TIMER_SHIFT)
	    );
}

/* CON6---------------------------------------------------- */

void bq24259_set_treg(unsigned int val)
{
	unsigned int ret = 0;

	ret = bq24259_config_interface((unsigned char) (bq24259_CON6),
				       (unsigned char) (val),
				       (unsigned char) (CON6_TREG_MASK), (unsigned char) (CON6_TREG_SHIFT)
	    );
}

void bq24259_set_boostv(unsigned int val)
{
	unsigned int ret = 0;

	ret = bq24259_config_interface((unsigned char) (bq24259_CON6),
				       (unsigned char) (val),
				       (unsigned char) (CON6_BOOSTV_MASK),
				       (unsigned char) (CON6_BOOSTV_SHIFT)
	    );
}

void bq24259_set_bhot(unsigned int val)
{
	unsigned int ret = 0;

	ret = bq24259_config_interface((unsigned char) (bq24259_CON6),
				       (unsigned char) (val),
				       (unsigned char) (CON6_BHOT_MASK), (unsigned char) (CON6_BHOT_SHIFT)
	    );
}

/* CON7---------------------------------------------------- */

void bq24259_set_tmr2x_en(unsigned int val)
{
	unsigned int ret = 0;

	ret = bq24259_config_interface((unsigned char) (bq24259_CON7),
				       (unsigned char) (val),
				       (unsigned char) (CON7_TMR2X_EN_MASK),
				       (unsigned char) (CON7_TMR2X_EN_SHIFT)
	    );
}

void bq24259_set_batfet_disable(unsigned int val)
{
	unsigned int ret = 0;

	ret = bq24259_config_interface((unsigned char) (bq24259_CON7),
				       (unsigned char) (val),
				       (unsigned char) (CON7_BATFET_Disable_MASK),
				       (unsigned char) (CON7_BATFET_Disable_SHIFT)
	    );
}

void bq24259_set_int_mask(unsigned int val)
{
	unsigned int ret = 0;

	ret = bq24259_config_interface((unsigned char) (bq24259_CON7),
				       (unsigned char) (val),
				       (unsigned char) (CON7_INT_MASK_MASK),
				       (unsigned char) (CON7_INT_MASK_SHIFT)
	    );
}

/* CON8---------------------------------------------------- */

unsigned int bq24259_get_system_status(void)
{
	unsigned int ret = 0;
	unsigned char val = 0;

	ret = bq24259_read_interface((unsigned char) (bq24259_CON8),
				     (&val), (unsigned char) (0xFF), (unsigned char) (0x0)
	    );
	return val;
}

unsigned int bq24259_get_vbus_stat(void)
{
	unsigned int ret = 0;
	unsigned char val = 0;

	ret = bq24259_read_interface((unsigned char) (bq24259_CON8),
				     (&val),
				     (unsigned char) (CON8_VBUS_STAT_MASK),
				     (unsigned char) (CON8_VBUS_STAT_SHIFT)
	    );
	return val;
}

unsigned int bq24259_get_chrg_stat(void)
{
	unsigned int ret = 0;
	unsigned char val = 0;

	ret = bq24259_read_interface((unsigned char) (bq24259_CON8),
				     (&val),
				     (unsigned char) (CON8_CHRG_STAT_MASK),
				     (unsigned char) (CON8_CHRG_STAT_SHIFT)
	    );
	return val;
}

unsigned int bq24259_get_vsys_stat(void)
{
	unsigned int ret = 0;
	unsigned char val = 0;

	ret = bq24259_read_interface((unsigned char) (bq24259_CON8),
				     (&val),
				     (unsigned char) (CON8_VSYS_STAT_MASK),
				     (unsigned char) (CON8_VSYS_STAT_SHIFT)
	    );
	return val;
}

/**********************************************************
  *
  *   [Internal Function]
  *
  *********************************************************/
void bq24259_hw_component_detect(void)
{
	unsigned int ret = 0;
	unsigned char val = 0;

	ret = bq24259_read_interface(0x0A, &val, 0xFF, 0x0);

	if (val == 0)
		g_bq24259_hw_exist = 0;
	else
		g_bq24259_hw_exist = 1;

	battery_log(BAT_LOG_CRTI, "[bq24259_hw_component_detect] exist=%d, Reg[0x03]=0x%x\n", g_bq24259_hw_exist, val);
}

int is_bq24259_exist(void)
{
	battery_log(BAT_LOG_CRTI, "[is_bq24259_exist] g_bq24259_hw_exist=%d\n", g_bq24259_hw_exist);

	return g_bq24259_hw_exist;
}

void bq24259_dump_register(void)
{
	int i = 0;
//lenovo-sw mahj2 modify for debug Begin
	battery_log(BAT_LOG_CRTI, "[bq24259] ");
	for (i = 0; i < bq24259_REG_NUM; i++) {
		bq24259_read_byte(i, &bq24259_reg[i]);
		battery_log(BAT_LOG_CRTI, "[0x%x]=0x%x\n", i, bq24259_reg[i]);
	}
	battery_log(BAT_LOG_CRTI, "\n");
//lenovo-sw mahj2 modify for debug End
}

static int bq24259_driver_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	int err = 0;

	battery_log(BAT_LOG_CRTI, "[bq24259_driver_probe]\n");

	new_client = kmalloc(sizeof(struct i2c_client), GFP_KERNEL);

	if (!new_client) {
		err = -ENOMEM;
		goto exit;
	}
	memset(new_client, 0, sizeof(struct i2c_client));

	new_client = client;
//lenovo-sw mahj2 add for board temp Begin
#ifdef bq24259_POWER_SUPPLY
	err = bq24259_power_supply_init(new_client);
	if (err) {
		pr_notice("[bq24259_power_supply_init] failed to register power supply: %d\n", err);
		goto exit;
	}	
#endif
//lenovo-sw mahj2 add for board temp End

	/* --------------------- */
	bq24259_hw_component_detect();
	bq24259_dump_register();
	chargin_hw_init_done = KAL_TRUE;

	return 0;

exit:
	return err;

}

/**********************************************************
  *
  *   [platform_driver API]
  *
  *********************************************************/
unsigned char g_reg_value_bq24259 = 0;
static ssize_t show_bq24259_access(struct device *dev, struct device_attribute *attr, char *buf)
{
	battery_log(BAT_LOG_CRTI, "[show_bq24259_access] 0x%x\n", g_reg_value_bq24259);
	return sprintf(buf, "%u\n", g_reg_value_bq24259);
}

static ssize_t store_bq24259_access(struct device *dev, struct device_attribute *attr,
				    const char *buf, size_t size)
{
	int ret = 0;
	char *pvalue = NULL, *addr, *val;
	unsigned int reg_value = 0;
	unsigned int reg_address = 0;

	battery_log(BAT_LOG_CRTI, "[store_bq24259_access]\n");

	if (buf != NULL && size != 0) {
		battery_log(BAT_LOG_CRTI, "[store_bq24259_access] buf is %s and size is %zu\n", buf, size);
		/*reg_address = kstrtoul(buf, 16, &pvalue);*/

		pvalue = (char *)buf;
		if (size > 3) {
			addr = strsep(&pvalue, " ");
			ret = kstrtou32(addr, 16, (unsigned int *)&reg_address);
		} else
			ret = kstrtou32(pvalue, 16, (unsigned int *)&reg_address);

		if (size > 3) {
			val = strsep(&pvalue, " ");
			ret = kstrtou32(val, 16, (unsigned int *)&reg_value);

			battery_log(BAT_LOG_CRTI,
			    "[store_bq24259_access] write bq24259 reg 0x%x with value 0x%x !\n",
			     reg_address, reg_value);
			ret = bq24259_config_interface(reg_address, reg_value, 0xFF, 0x0);
		} else {
			ret = bq24259_read_interface(reg_address, &g_reg_value_bq24259, 0xFF, 0x0);
			battery_log(BAT_LOG_CRTI,
			    "[store_bq24259_access] read bq24259 reg 0x%x with value 0x%x !\n",
			     reg_address, g_reg_value_bq24259);
			battery_log(BAT_LOG_CRTI,
			    "[store_bq24259_access] Please use \"cat bq24259_access\" to get value\r\n");
		}
	}
	return size;
}

static DEVICE_ATTR(bq24259_access, 0664, show_bq24259_access, store_bq24259_access);	/* 664 */

/*Start lenovo chailu1 add  for usr space read ic ID 20150521*/
static ssize_t show_bq24259_id(struct device *dev,struct device_attribute *attr, char *buf)
{
    unsigned char  tmp;

     bq24259_read_byte(0x0A, &tmp);
     tmp &= 0xe0;
     printk("tmp=0x%X\n", tmp);

    if (tmp == 0x20)
        return snprintf(buf, 10, "%s\n", "BQ24259");
    else
	 return snprintf(buf, 10, "%s\n", "ERROR");
}
static ssize_t store_bq24259_id(struct device *dev,struct device_attribute *attr, const char *buf, size_t size)
{
    return size;
}

static DEVICE_ATTR(bq24259_id, 0664, show_bq24259_id, store_bq24259_id); //664
/*End  lenovo chailu1 add  for usr space read ic ID 20150521*/

static int bq24259_user_space_probe(struct platform_device *dev)
{
	int ret_device_file = 0;

	battery_log(BAT_LOG_CRTI, "******** bq24259_user_space_probe!! ********\n");

	ret_device_file = device_create_file(&(dev->dev), &dev_attr_bq24259_access);
	
/*Start lenovo chailu1 add  for usr space read ic ID 20150521*/
    ret_device_file = device_create_file(&(dev->dev), &dev_attr_bq24259_id);	
/*End  lenovo chailu1 add  for usr space read ic ID 20150521*/
	
	return 0;
}

struct platform_device bq24259_user_space_device = {
	.name = "bq24259-user",
	.id = -1,
};

static struct platform_driver bq24259_user_space_driver = {
	.probe = bq24259_user_space_probe,
	.driver = {
		   .name = "bq24259-user",
		   },
};

static int __init bq24259_subsys_init(void)
{
	int ret = 0;
#ifdef CONFIG_OF
	battery_log(BAT_LOG_CRTI, "[bq24259_init] init start with i2c DTS");
#else
//lenovo-sw mahj2 modify at 20150318 Begin
    i2c_register_board_info(bq24259_BUSNUM, &i2c_bq24259, 1);
//lenovo-sw mahj2 modify at 20150318 End
#endif
	if (i2c_add_driver(&bq24259_driver) != 0)
		battery_log(BAT_LOG_CRTI, "[bq24259_init] failed to register bq24259 i2c driver.\n");
	else
		battery_log(BAT_LOG_CRTI, "[bq24259_init] Success to register bq24259 i2c driver.\n");

	/* bq24259 user space access interface */
	ret = platform_device_register(&bq24259_user_space_device);
	if (ret) {
		battery_log(BAT_LOG_CRTI, "****[bq24259_init] Unable to device register(%d)\n", ret);
		return ret;
	}
	ret = platform_driver_register(&bq24259_user_space_driver);
	if (ret) {
		battery_log(BAT_LOG_CRTI, "****[bq24259_init] Unable to register driver (%d)\n", ret);
		return ret;
	}

	return 0;
}

static void __exit bq24259_exit(void)
{
	i2c_del_driver(&bq24259_driver);
}

/* module_init(bq24259_init); */
/* module_exit(bq24259_exit); */
subsys_initcall(bq24259_subsys_init);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("I2C bq24259 Driver");
MODULE_AUTHOR("YT Lee<yt.lee@mediatek.com>");

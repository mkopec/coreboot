/* SPDX-License-Identifier: GPL-2.0-only */

Device(EC)
{
	Name (_HID, EISAID("PNP0C09"))
	Name (_UID, 0)
	Name (_GPE, 16)
	Name (ECRD, 0)

	Name (_CRS, ResourceTemplate ()
	{
		IO (Decode16,
			0x0930,             // Range Minimum
			0x0930,             // Range Maximum
			0x00,               // Alignment
			0x01                // Length
			)
		IO (Decode16,
			0x0934,             // Range Minimum
			0x0934,             // Range Maximum
			0x00,               // Alignment
			0x01                // Length
			)
	})

	Method (_STA, 0, Serialized)  // _STA: Status
	{
		Return (0x0F)
	}

	Method (_REG, 2, NotSerialized)
	{
		LIDS = EC03
		EC05 = 1
		EC01 = 0x40 // EC Linux mode
		ECRD = 1
	}

	Method (_Q66, 0, NotSerialized)
	{
		Debug = "EC: _Q66"
	}

	OperationRegion (ECOR, EmbeddedControl, Zero, 0xFF)
	Field (ECOR, ByteAcc, Lock, Preserve)
	{
		EC00,   8,
		EC01,   8,
		EC02,   8,
		EC03,   8,
		EC04,   8,
		EC05,   8,
		EC06,   8,
		EC07,   8,
		EC08,   8,
		EC09,   8,
		EC10,   8,
		EC11,   8,
		EC12,   8,
		EC13,   8,
		EC14,   8,
		EC15,   8,
		EC16,   8,
		EC17,   8,
		EC18,   8,
		EC19,   8,
		EC20,   8,
		EC21,   8,
		EC22,   8,
		EC23,   8,
		EC24,   8,
		EC25,   8,
		EC26,   8,
		EC27,   8,
		EC28,   8,
		EC29,   8,
		EC30,   8,
		EC31,   8,
		EC32,   8,
		EC33,   8,
		EC34,   8,
		EC35,   8,
		EC36,   8,
		EC37,   8,
		EC38,   8,
		EC39,   8,
		EC40,   8,
		EC41,   8,
		EC42,   8,
		EC43,   8,
		EC44,   8,
		EC45,   8,
		EC46,   8,
		EC47,   8,
		EC48,   8,
		EC49,   8
	}
}

.PHONY: ninja
ninja: bin/cc1-psx-26 $(MASPSX_APP) $(SOTNASSETS)
	VERSION=$(VERSION) python3 tools/builds/gen.py
	ninja

.PHONY: extract_us
extract_us:
	VERSION=us python3 tools/builds/gen.py
	ninja build/us/dra.ld
.PHONY: extract_hd
extract_hd:
	VERSION=hd python3 tools/builds/gen.py
	ninja build/hd/dra.ld

extract_disk_us: extract_disk_psxus
extract_disk_hd: extract_disk_pspeu
extract_disk_psx%: $(SOTNDISK)
	$(SOTNDISK) extract disks/sotn.$*.cue disks/$* > /dev/null

.PHONY: build_us
build_us: ninja
.PHONY: build_hd
build_hd: ninja

extract_assets: config/assets.$(VERSION).yaml $(SOTNASSETS)
	cd tools/sotn-assets; $(GO) install
	$(SOTNASSETS) extract $<
build_assets: config/assets.$(VERSION).yaml $(SOTNASSETS)
	$(SOTNASSETS) build $<

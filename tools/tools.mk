test:
	$(PYTHON) tools/symbols_test.py

function-finder:
	# TODO: make sure graphviz is installed
	$(MAKE) force_symbols
	$(MAKE) force_extract
	$(PYTHON) tools/analyze_calls.py
	git clean -fdx asm/
	git checkout config/
	rm -f build/us/main.ld
	rm -rf build/us/weapon.ld
	$(MAKE) -j extract
	$(PYTHON) tools/function_finder/function_finder_psx.py --use-call-trees > gh-duplicates/functions.md
	rm -rf gh-duplicates/function_calls || true
	mv function_calls gh-duplicates/
	mv function_graphs.md gh-duplicates/

duplicates-report:
	$(MAKE) force_symbols
	$(MAKE) force_extract
	cd tools/dups; \
	    cargo run --release -- \
            --threshold .90 \
            --output-file ../../gh-duplicates/duplicates.txt

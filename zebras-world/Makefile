PYTHON = python
REQUIRES = "python"

all: rpm clean

egg:
	$(PYTHON) setup.py bdist_egg

rpm:
	@echo '[bdist_rpm]' > setup.cfg
	@echo -n 'changelog = ' >> setup.cfg
	@git log --format="* %cd %aN%n- (%h) %s%d%n" --date=local -- . | sed -r 's/[0-9]+:[0-9]+:[0-9]+ //' | sed 's/^\(.*\)/ \1/g' >> setup.cfg
	$(PYTHON) setup.py bdist_rpm --packager="Miroslav Franc <mfranc@gmx.com>" --requires=$(REQUIRES) --no-autoreq

clean:
	-rm -rf build/  zebras_world.egg-info/ setup.cfg

mrproper: clean
	-rm -rf dist/

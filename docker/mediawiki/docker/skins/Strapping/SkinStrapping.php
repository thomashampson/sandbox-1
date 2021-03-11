<?php

/**
 * Skin subclass for Strapping
 * @ingroup Skins
 * @final skins extending SkinVector are not supported
 */
class SkinStrapping extends SkinTemplate {
    public $skinname = 'strapping';
	public $stylename = 'Strapping';
	public $template = 'StrappingTemplate';

    /**
	 * @inheritDoc
	 * @return array
	 */
	public function getDefaultModules() {
		$modules = parent::getDefaultModules();

        $modules['styles'] = array_merge(
            $modules['styles'],
            [ 'skins.strapping.styles', 'mediawiki.ui.icon', 'skins.strapping.icons' ]
        );
        $modules['strapping'][] = 'skins.strapping.js';

		return $modules;
	}
}
<?php

/**
 * Implements hook_drush_command().
 */
function replicate_drush_command() {

  $items['drush-demo-command'] = array(
    'description' => 'Demonstrate how Drush commands work.',
    'aliases' => array('ddc'),
  );

  return $items;
}

/**
 * Callback for the drush-demo-command command
 */
function drush_replicate_drush_demo_command() {
  replicate_print_statement();
}

function drush_replicate_drush_help($command) {
  switch ($command) {
    case 'drush:my-command':
      return dt('Run my command');
  }
}
function replicate_print_statement() {
  drupal_set_message(t('Hello world!'));
}
/*
 * Implements hook_drush_command().
 

function drush_replicate_drush_command() {
  $items = array();
  $items['replicate'] = array(
    'description' => 'Replicate an Enitity via Drush!',
    'arguments' => array(
      'entity-type' => dt('Type of Entity (eg. Node) that you wish to replicate'),
    ),
    'arguments' => array(
      'id-number' => dt('ID value of the specified Entity Type (eg. NodeID'),
    ),
    'aliases' => array('rep'),
    'examples' => array(
      'drush replicate node 1' =>
        'Node 1 is replicated via drush using full command',
      'drush rep node 1' =>
        'Node 1 is replicated via drush using aliased command',
    ),
  );
  return $items;
}
*/
/**
 * Callback for the drush-demo-command command
 */
/**
 * Callback function for drush my-command. 
 * Callback is called by using drush_hook_command() where
 * hook is the name of the module (MYMODULE) and command is the name of
 * the Drush command with all "-" characters converted to "_" characters (my_command)
 *
 * @param $arg1
 *   An optional argument
 */
function drush_replicate_drush_replicate_drush_command($arg1 = NULL) {
  //check if the argument was passed in and just print it out
  if (isset($arg1)) {
   drush_print($arg1);
  }
 
  //log to the command line with an OK status
  drush_log('Running my-command', 'ok');
}
/**
 * Replicate the entity corresponding to the type and id passed in argument and save it.
 *
 * @param string $entity_type
 *   The entity type.
 * @param int $id
 *   The unique entity identifier.
 *
 * @return mixed
 *   The newly created entity id if the clone has been created and saved,
 *   else FALSE.
 *
 * @see replicate_entity()
 */
function drush_replicate_drush_entity_by_id($entity_type, $id) {
  $original = entity_load_single($entity_type, $id);
  return replicate_drush_entity($entity_type, $original);
}
/**
 * Replicate the entity passed in argument and save it.
 *
 * @param string $entity_type
 *   The entity type.
 * @param object $entity
 *   The entity to replicate.
 *
 * @return mixed
 *   The newly created entity id if the clone has been created and saved,
 *   else FALSE.
 */
function drush_replicate_drush_entity($entity_type, $entity) {
	//
	// TODO MJM: The goal here is to create a cloned entity. First we will read the information from the 
	// Entity that is being targeted and store it in an Object(?). Next we will take that Entity and do 
	// an entity Create with the entity passed into it.  This will require us to modify the 
	// drush_entity_create() function to allow for a passed in object.  The infos will be read
	// out of the passed in Object and then will be created again with a new nid or enity id of that type
	// Need to veriy if nodes will also be able to work in this.
	//
  $clone = replicate_clone_entity($entity_type, $entity);
  if ($clone) {
    //$entityids = entity_extract_ids($entity_type, $entity);
    //$lastentityid = array_pop($entityids);
    entity_save($entity_type, $clone);
      list($entity_id) = entity_extract_ids($entity_type, $clone);

    if (isset($entity_id)) {
      return $entity_id;
    }
  }

  return FALSE;
}

/**
 * Create an entity by the given type.
 *
 * @param $entity_type
 *   The entity type to create.
 * @param $file
 *   The (optional) source file to create entities from.
 */
function drush_replicte_drush_entity_create($entity_type = NULL, $file = NULL) {
  if (!$entity_type) {
    drush_set_error('DRUSH_ENTITY_CREATE_ERROR', dt('You must specify an entity type'));
    return;
  }

  _drush_entity_check_type($entity_type);

  if (empty($file)) {
    $entity_class = isset($entity_info['entity class']) ? $entity_info['entity class'] : 'stdClass';
    $entity = new $entity_class();
    // Create defaults on the entity object.
    if (isset($entity_info['drush']['defaults'])) {
      foreach ($entity_info['drush']['defaults'] as $key => $value) {
        $entity->$key = $value;
      }
    }
    $entity_json = _drush_entity_edit_string(drush_json_encode($entity));
  }
  else if ($file === '-' || file_exists($file)) {
    if ($file === '-') {
      $entity_json = stream_get_contents(STDIN);
    }
    else {
      drush_log("Reading file $file");
      $entity_json = file_get_contents($file);
    }
  }
  else {
    drush_set_error('DRUSH_ENTITY_CREATE_ERROR', dt('Improper input/args'));
  }

  if (!empty($entity_json)) {
    $entities = drush_json_decode($entity_json);
    // The file contains an array of entity objects.
		if (is_array($entities)) {
			foreach ($entities as $entity_array) {
				$entity = (object) $entity_array;
				_drush_entity_create_entity($entity_type, $entity);
			}
		}
    // The files has just one entity object.
		else {
			$entity = $entities;
			_drush_entity_create_entity($entity_type, $entity);
		}
  }
	else if ($file === '-') {
		drush_set_error('DRUSH_NO_STDIN', dt('stdin empty!'));
	}
	else {
		drush_set_error('DRUSH_EMPTY_FILE', dt('Empty file!'));
	}
}


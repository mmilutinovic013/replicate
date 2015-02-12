<?php

/**
 * Implements hook_drush_command().
 */
function replicate_drush_command() {
  $items = array();
  $items['replicate-drush-entity-by-id'] = array(
    'description' => 'Replicate an Enitity via Drush!',
    'arguments' => array(
      'entity-type' => dt('Type of Entity (eg. Node) that you wish to replicate'),
    ),
    'arguments' => array(
      'id-number' => dt('ID value of the specified Entity Type (eg. NodeID'),
    ),
    'aliases' => array('drep'),
    'examples' => array(
      'drush replicate node 1' =>
        'Node 1 is replicated via drush using full command',
      'drush rep node 1' =>
        'Node 1 is replicated via drush using aliased command',
    ),
  );
  return $items;
}

/**
 * Callback for the drush-demo-command command
 */
function drush_replicate_drush_demo_command() {
  drush_replicate_print_statement();
}

function drush_replicate_drush_help($command) {
  switch ($command) {
    case 'drush:my-command':
      return dt('Run my command');
  }
}

function drush_replicate_drush_entity_by_id($entity_type, $id) {
  
  if(!$info = entity_get_info($entity_type)){
      drush_print('Entity does not exist! Please enter a valid entity type and number!');
      return FALSE;
  }
  $original = entity_load_single($entity_type, $id);
  return drush_replicate_drush_entity($entity_type, $original);
}

function drush_replicate_drush_entity($entity_type, $entity) {
  if($entity && $entity_type){
    $clone = drush_replicate_replicate_clone_entity($entity_type, $entity);
    if ($clone) {
      //$entityids = entity_extract_ids($entity_type, $entity);
      //$lastentityid = array_pop($entityids);
      entity_save($entity_type, $clone);
        list($entity_id) = entity_extract_ids($entity_type, $clone);

      if (isset($entity_id)) {
        return $entity_id;
      }
    }
  }
  drush_print('Entity does not exist! Please enter a valid entity type and number!');
  return FALSE;
}

function drush_replicate_replicate_clone_entity($entity_type, $entity) {
  $clone = clone($entity);

  if ($clone) {
    // Let other modules manage the cleaning of the entity.
    foreach (module_implements('replicate_entity_' . $entity_type) as $module) {
      $function = $module . '_replicate_entity_' . $entity_type;
      $function($clone);
    }

    // Set the entity as new entity.
    $clone->is_new = TRUE;

    // Let other modules do special actions on each field.
    replicate_clone_fields($clone, $entity_type);

    // Let other modules do special actions on the global entity.
    drupal_alter('replicate_entity', $clone, $entity_type, $entity);
  }

  return $clone;
}